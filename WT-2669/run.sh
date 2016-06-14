#!/bin/bash

#Steering Variables
RUNDIR=`pwd`

## Defaults for user variables
# The mongodb version to use for tests if not compiling
MONGODIR=$RUNDIR/newer_build/mongodb-linux-x86_64-3.3.8-21-g2559d31
# The mongodb version to use for baseline if not compiling
MONGO_BASE=$RUNDIR/default_build/mongodb-linux-x86_64-3.3.6-229-ge533634
# The path to the YCSB binary
YCSB_BIN=~/work/jira/w2669/YCSB/bin/ycsb
# The size of the WT cache to use in GBs, 0 is system default
CACHE_SIZE=5

# The following shouldn't need to be changed.
MONGO_SOURCE=$RUNDIR/mongo-source
DBPATH=$MONGODIR/db
SUITE=$RUNDIR/suite
LOGDIR=$RUNDIR/log
RUN_LOG=$LOGDIR/run.log
MON_FILE=$LOGDIR/monitor.log
BASELINE_FILE=$SUITE/baseline.out
RUN_PERF_FILE=$LOGDIR/perf_final.log
MON_PID=0
FRAG_LIMIT=50
PERF_LIMIT=0.1
TIMER=0
PERF_FAILED=0

SYSPERF_WORKLOADS="contended_update.js insert_capped_indexes.js insert_capped.js insert_ttl.js jtrue.js"

# Suites
YCSB=0
LOCAL=0
EVG=0
BASELINE=0
COMPILE=0

function print_help {
	echo "run.sh --suites=[local,ycsb,evg] --baseline"
	exit 1;
}

function pass_args {
	# If we have no args, run the whole shebang
	if [ "$1" == "" ]; then
		YCSB=1
		LOCAL=1
		EVG=1
		return
	fi
	if [ "$1" == "--help" ]; then
		print_help
	fi
	for var in "$@"
	do
		case $var in 
		--suites*)
			SUITES=`echo $var | awk -F= '{print $2}'`
			IFS=', ' read -r -a array <<< "$SUITES"
			for suite in "${array[@]}"	
			do
				case $suite in
				ycsb)
					YCSB=1
					;;
				local)
					LOCAL=1
					;;
				evg)
					EVG=1
					;;
				*)
					print_help
					;;	
				esac
			done
			;;
		--baseline)
			if [ -f $BASELINE_FILE ]; then
				echo "Baseline file exists. To re-gather please delete $BASELINE_FILE and re-run." | tee -a $RUN_LOG
			else
				echo "Warning: Baseline gathering can take some time, so be prepared to wait" | tee -a $RUN_LOG
				BASELINE=1
			fi
			;;
		--compile)
			COMPILE=1
			MONGODIR=$MONGO_SOURCE
			MONGO_BASE=$MONGO_SOURCE
			;;
		*)
			print_help
		esac
	done
}

function get_repos {
	git clone https://github.com/mongodb/mongo.git $MONGO_SOURCE 2>&1
	if [ $((EVG+BASELINE)) -ne 0 ]; then
		git clone git@github.com:10gen/workloads.git 2>&1
		git clone https://github.com/mongodb/mongo-perf 2>&1
	fi
}

# Pull down git repo and compile 
function make_mongo {
	# We compile only when requested
	if [ $COMPILE -ne 0 ]; then
		cd $MONGO_SOURCE 
		git checkout master
		# Update wiredtiger code can be added here
		scons -j10 core --disable-warnings-as-errors
		cd ..
	fi
}
# Stop and MongoDB instances, cleanup the dbapth
function clean_mongod {
	killall -q -9 mongod 2>&1 > /dev/null
	sleep 5
	rm -rf $DBPATH
	mkdir $DBPATH
}

# Start a mongodb instance
function start_mongod {
	if [ $CACHE_SIZE -eq 0 ]; then
		$1/mongod --logpath=$LOGDIR/mongodb.log --dbpath=$DBPATH --fork --nojournal --quiet > /dev/null
	else
		$1/mongod --logpath=$LOGDIR/mongodb.log --dbpath=$DBPATH --wiredTigerCacheSizeGB=$CACHE_SIZE --fork --nojournal --quiet > /dev/null
	fi
	sleep 5;
}

# MongoDB should still be running when this is called. Check if it crashed - we expect that the
# OOMKiller may get involved here!
function check_mongo {
	cp -rp $DBPATH/diagnostic.data $LOGDIR/$1-diag
	RES=`ps -ef | grep mongod | grep -v grep | wc -l`
	if [ $RES -eq 0 ]; then
	        echo "Test for $1 failed" | tee -a $RUN_LOG
	        echo "Test failed as MongoDB crashed, potentially due to OOM killer" | tee -a $RUN_LOG
	        #exit 1
	fi

}

# Start the monitor thread to capture $MON_FILE
function start_monitor {
	if [ -f $MON_FILE ]; then
		rm $MON_FILE
	fi
	$MONGODIR/mongo > $MON_FILE --quiet --eval \
        "while(true) {
		var out = db.serverStatus({tcmalloc:1});
		var heapsize = out.tcmalloc.generic.heap_size;
		var allocated = out.tcmalloc.generic.current_allocated_bytes;
		print((heapsize-allocated)/allocated*100);
		sleep(1000*1);
	}" &
	MON_PID=$!
	# Supress the terminated messages
	disown
	$MONGODIR/mongo > $MON_FILE.jemalloc --quiet --eval \
	"while(true) {                                                          
                var out = db.serverStatus({tcmalloc:1});                        
                var heapsize = out.mem.resident*1024*1024;                  
                var allocated = out.wiredtiger.cache['bytes currently in the cache'];   
                print((heapsize-allocated)/allocated*100);                      
                sleep(1000*1);                                                  
        }" &
}

# Stop the Monitor thread
function stop_monitor {
	kill $MON_PID
}

# Check if the monitor file shows that we have exceeded the expected fragmentation limit
# This is the FRAG_LIMIT global variable
function check_monitor {
	if [ ! -f $MON_FILE ]; then
		echo "ERROR: Monitor file $MON_FILE, not found." | tee -a $RUN_LOG
		#exit 1;
	fi
	RES=`cat $MON_FILE | awk -F "." '{print $1}' | sort -n | uniq | tail -n 1`
	if [ $RES -ge $FRAG_LIMIT ]; then
		echo "Fragmentation over limit for test $1. Max recorded fragmentation is $RES" | tee -a $RUN_LOG
		#exit 1;
	fi
}

# Load phase of YCSB, takes the YCSB file as an argument
function load_ycsb {
	$YCSB_BIN load mongodb -s -P $1 -threads 15 2>&1
}

# Run phase of YCSB, takes the YCSB file as an argument
function run_ycsb {
	$YCSB_BIN run mongodb -s -P $1 -threads 15 2>&1
}

function start_timer {
	TIMER=`date "+%s"`
}

function end_timer {
	TIMER_END=`date "+%s"`
	echo "Run took: $((TIMER_END-TIMER))s" | tee -a $RUN_LOG
}

# Run Evergreen stuff to gether 
function gather_baseline {
        echo "Starting Evergreen Baseline" | tee -a $RUN_LOG
        echo "Starting a mongo-perf baseline" | tee -a $RUN_LOG
	if [ -d $MONGO_BASE/bin ]; then
		MONGO_BASE=$MONGO_BASE/bin
	fi
        # mongo-perf run
        clean_mongod
        start_mongod $MONGO_BASE
        start_timer
        cd $RUNDIR/mongo-perf
        stdbuf -oL python benchrun.py --shell $MONGO_BASE/mongo -t 1 8 --trialCount 1 \
                -f testcases/*.js --includeFilter insert misc update query \
                --includeFilter core regression --excludeFilter single_threaded \
                --out $LOGDIR/perf_baseline.json --exclude-testbed > $LOGDIR/mongo-perf-baseline.log 2>&1
        cd $RUNDIR
        end_timer
        check_mongo "mongo-perf-baseline"

        echo "Starting a sys-perf baseline" | tee -a $RUN_LOG
        clean_mongod
        start_mongod $MONGO_BASE
        start_timer
        cd $RUNDIR/workloads
        stdbuf -oL python run_workloads.py --shell $MONGO_BASE/mongo -w $SYSPERF_WORKLOADS > $LOGDIR/sys-perf-baseline.log
	cd $RUNDIR
        end_timer
        check_mongo "sys-perf-baseline"
	egrep -v "Finished|mongoPerf|version|connecting|load|^$|`cd $MONGO_BASE; ./mongod --version | grep git | awk '{print $3}'; cd $RUNDIR`" $LOGDIR/mongo-perf-baseline.log > $BASELINE_FILE
	egrep ">>>" $LOGDIR/sys-perf-baseline.log >> $BASELINE_FILE
}

# Compare this runs perf to the baseline
function compare_perf {
	RES=python $RUNDIR/perf-compare.py $BASELINE_FILE $RUN_PERF_FILE
}

# Main
# We run the following suite of tests
# - allocator_fragmentation.js added in SERVER-23333
# - Workload shell script from SERVER-20306
# - Workload workload js script from SERVER-22906
# - A YCSB workload from SERVER-24207
# - A YCSB workload defined for this this suite (WT-2669)
# - The equivalent of the evergreen performance and sys-perf suites

# Basic setup stuff
rm -rf $LOGDIR
mkdir $LOGDIR
touch $RUN_LOG
pass_args $@
echo "Performing setup" | tee -a $RUN_LOG
if [ -d $MONGODIR/bin ]; then
	MONGODIR=$MONGODIR/bin
fi

# First we grab all the repos we need to run these tests
get_repos > $LOGDIR/fetch.log
# Now we make MongoDB
make_mongo > $LOGDIR/make.log

# Gather a baseline for perf analysis
if [ $BASELINE -ne 0 ]; then
	echo "Gathering baseline for Evergreen Runs. This WILL take some time so bare with us" | tee -a $RUN_LOG
	if [ -f $BASELINE_FILE ]; then
		cp $BASELINE_FILE $BASELINE_FILE.bkp
	fi
	gather_baseline
fi

# Run the suites, if selected
if [ $LOCAL -ne 0 ]; then
	echo "Starting local worklaods" | tee -a $RUN_LOG
	# SERVER-23333 workload
	echo "SERVER-23333" | tee -a $RUN_LOG
	cd $MONGO_SOURCE
	# The resmoke scripts' --mongo and --mongod options are broken, work around this
        if [ "$MONGO_SOURCE" != "$MONGODIR" ]; then
                cp $MONGODIR/mongo $MONGO_SOURCE
                cp $MONGODIR/mongod $MONGO_SOURCE
        fi
        start_timer
        stdbuf -oL python buildscripts/resmoke.py --dbpathPrefix=$LOGDIR --executor=no_passthrough_with_mongod $SUITE/SERVER-23333.js --log=file > $LOGDIR/SERVER-23333.log 2>&1
	RES=$?
	end_timer
	if [ $RES -ne 0 ]; then
		echo "Test for SERVER-23333 failed" | tee -a $RUN_LOG
		echo "Error(s) from log were:" | tee -a $RUN_LOG
		grep "assert failed" $MONGO_SOURCE/tests.log
		#exit 1
	fi
	cd $RUNDIR

	# SERVER-20306 workload
	echo "Starting SERVER-20306" | tee -a $RUN_LOG
	clean_mongod
	start_mongod $MONGODIR
	start_monitor
	cd $MONGODIR
	start_timer
	sh $SUITE/SERVER-20306.sh > $LOGDIR/SERVER-20306.log
	end_timer
	stop_monitor > /dev/null
	check_monitor "SERVER-20306"
	check_mongo "SERVER-20306"
	cd $RUNDIR

	# SERVER-22906 workload
	echo "Starting SERVER-22906" | tee -a $RUN_LOG
	clean_mongod
	start_mongod $MONGODIR
	start_monitor
	start_timer
	for i in $(seq 1 9); do
		$MONGODIR/mongo --quiet $SUITE/SERVER-22906.js &
	done
	$MONGODIR/mongo --quiet $SUITE/SERVER-22906.js
	end_timer
	# Wait for the other threads
	sleep 10
	stop_monitor > /dev/null
	check_mongo "SERVER-22906"
	check_monitor "SERVER-22906"
fi

if [ $YCSB -ne 0 ]; then
	echo "Starting YCSB Workloads" | tee -a $RUN_LOG
	# SERVER-24207 workload
	echo "Starting SERVER-24207" | tee -a $RUN_LOG
	clean_mongod
	start_mongod $MONGODIR
	start_monitor
	start_timer
	load_ycsb $SUITE/SERVER-24207.ycsb > $LOGDIR/SERVER-24207-load.log
	end_timer
	stop_monitor
	check_mongo "SERVER-24207"
	check_monitor "SERVER-24207"

	# Custom smalldoc's workload for this suite
	echo "Starting WT-2669" | tee -a $RUN_LOG
	clean_mongod
	start_mongod $MONGODIR
	start_monitor
	start_timer
	load_ycsb $SUITE/WT-2669.ycsb > $LOGDIR/WT-2669-load.log
	stop_monitor
	check_monitor "WT-2669-load"
	start_monitor
	check_mongo "WT-2669-load"
	run_ycsb $SUITE/WT-2669.ycsb > $LOGDIR/WT-2669-run.log
	end_timer
	stop_monitor
	check_mongo "WT-2669-run"
	check_monitor "WT-2669-run"
fi

if [ $EVG -ne 0 ]; then
	if [ ! -f $BASELINE_FILE ]; then
		echo "No baseline file available. Please run '$0 --baseline' to gather one" | tee -a $RUN_LOG
		echo "Without a baseline, there can be no comparison. Exiting" | tee -a $RUN_LOG
		exit 0;
	fi
	echo "Starting Evergreen Workloads" | tee -a $RUN_LOG
	echo "Starting a mongo-perf run" | tee -a $RUN_LOG
	# mongo-perf run
	clean_mongod
        start_mongod $MONGODIR
        start_timer
	cd $RUNDIR/mongo-perf
	stdbuf -oL python benchrun.py --shell $MONGODIR/mongo -t 1 8 --trialCount 1 \
                -f testcases/*.js --includeFilter insert misc update query \
                --includeFilter core regression --excludeFilter single_threaded \
                --out $LOGDIR/perf.json --exclude-testbed > $LOGDIR/mongo-perf.log 2>&1
	cd $RUNDIR
	end_timer
	check_mongo "mongo-perf"

	echo "Starting a sys-perf run" | tee -a $RUN_LOG
	clean_mongod
        start_mongod $MONGODIR
        start_timer
	cd $RUNDIR/workloads
	stdbuf -oL python run_workloads.py --shell $MONGODIR/mongo -w $SYSPERF_WORKLOADS > $LOGDIR/sys-perf.log
	cd $RUNDIR
        end_timer
        check_mongo "sys-perf"
	egrep -v "Finished|mongoPerf|version|connecting|load|^$|`cd $MONGODIR; ./mongod --version | grep git | awk '{print $3}'; cd ..`" $LOGDIR/mongo-perf.log > $RUN_PERF_FILE
        egrep ">>>" $LOGDIR/sys-perf.log >> $RUN_PERF_FILE
	compare_perf
fi
