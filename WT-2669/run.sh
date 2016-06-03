RUNDIR=`pwd`
MONGODIR=$RUNDIR/mongo
DBPATH=$MONGODIR/db
SUITE=$RUNDIR/suite
YCSB_BIN=~/work/ycsb/bin/ycsb
LOGDIR=$RUNDIR/log
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
	SPLIT=`echo $1 | awk -F= '{print $1}'`
	SUITES=`echo $1 | awk -F= '{print $2}'`
	IFS=', ' read -r -a array <<< "$SUITES"
	case $SPLIT in 
	--suites)
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
			echo "Baseline file exists. To re-gather please delete $BASELINE_FILE and re-run."
		else
			echo "Warning: Baseline gathering can take some time, so be prepared to wait"
			BASELINE=1
		fi
		;;
	*)
		print_help
	esac
}

function get_repos {
	git clone git@github.com:mongodb/mongo.git 2>&1
	if [ $((EVG+BASELINE)) -ne 0 ]; then
		git clone git@github.com:10gen/workloads.git 2>&1
		git clone https://github.com/mongodb/mongo-perf 2>&1
	fi
}

# Pull down git repo and compile 
function make_mongo {
	git clone http://github.com/mongodb/mongo
	cd $MONGODIR 
	git checkout master
	# Update wiredtiger code can be added here
	scons -j10 core --disable-warnings-as-errors
	cd ..
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
	$MONGODIR/mongod --logpath=$LOGDIR/mongodb.log --dbpath=$DBPATH --fork --nojournal --quiet > /dev/null
	sleep 5;
}

# MongoDB should still be running when this is called. Check if it crashed - we expect that the
# OOMKiller may get involved here!
function check_mongo {
	RES=`ps -ef | grep mongod | grep -v grep | wc -l`
	if [ $RES -eq 0 ]; then
	        echo "Test for SERVER-23333 failed"
	        echo "Test failed as MongoDB crashed, potentially due to OOM killer"
	        exit 1
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
}

# Stop the Monitor thread
function stop_monitor {
	kill $MON_PID
}

# Check if the monitor file shows that we have exceeded the expected fragmentation limit
# This is the FRAG_LIMIT global variable
function check_monitor {
	if [ ! -f $MON_FILE ]; then
		echo "ERROR: Monitor file $MON_FILE, not found."
		exit 1;
	fi
	RES=`cat $MON_FILE | awk -F "." '{print $1}' | sort -n | uniq | tail -n 1`
	if [ $RES -ge $FRAG_LIMIT ]; then
		echo "Fragmentation over limit for test $1. Max recorded fragmentation is $RES";
#		exit 1;
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
	echo "Run took: $((TIMER_END-TIMER))s"
}

# Run Evergreen stuff to gether 
function gather_baseline {
        echo "Starting Evergreen Baseline"
        echo "Starting a mongo-perf baseline"
        # mongo-perf run
        clean_mongod
        start_mongod
        start_timer
        cd $RUNDIR/mongo-perf
        stdbuf -oL python benchrun.py --shell $MONGODIR/mongo -t 1 8 --trialCount 1 \
                -f testcases/*.js --includeFilter insert misc update query \
                --includeFilter core regression --excludeFilter single_threaded \
                --out $LOGDIR/perf_baseline.json --exclude-testbed > $LOGDIR/mongo-perf-baseline.log 2>&1
        cd $RUNDIR
        end_timer
        check_mongo

        echo "Starting a sys-perf baseline"
        clean_mongod
        start_mongod
        start_timer
        cd $RUNDIR/workloads
        stdbuf -oL python run_workloads.py --shell $MONGODIR/mongo -w $SYSPERF_WORKLOADS > $LOGDIR/sys-perf-baseline.log
	cd $RUNDIR
        end_timer
        check_mongo
	egrep -v "Finished|mongoPerf|version|connecting|load|^$|`cd $MONGODIR; git show-ref -s | head -n1; cd ..`" $LOGDIR/mongo-perf-baseline.log > $BASELINE_FILE
	egrep ">>>" $LOGDIR/sys-perf-baseline.log >> $BASELINE_FILE
}

# Compare a sys-perf run result to baseline
# Format of a sysperf line is ">>> insert_capped : 55309.09872621494 64"
function comp_sysperf {
	IFS=' ' read -r -a array <<< "$line"
	title=${array[1]}
	value=${array[3]}
	threads=${array[4]}
	grep $title $RUN_PERF_FILE | while read -r line
	do
		IFS=' ' read -r -a array <<< "$outline"
		if [ $threads -eq ${array[4]} ]; then
			RES=`echo "(${array[3]} - ($value * $PERF_LIMIT)) > 0 | bc"`
			if [ $RES -ne 1 ]; then
				echo "Sysperf run: $title-$threads failed"
				echo "\t Baseline: $value vs ${array[3]} not within limit"
				PERF_FAILED=1 
			fi
		fi
	done
}

# Compare a monog-perf run to baseline 
# Format for a mongo-perf result is as the following BLOCK
# Insert.SingleIndex.Uncontested.Rnd
# 1	32862.598152605075
# 8	119026.92007014854
function comp_mongoperf {
	baseline_res=`grep -A2 $1 $BASELINE_FILE`
	perfrun_res=`grep -A2 $1 $RUN_PERF_FILE`
	IFS=$'\n' eval 'result_array=($perfrun_res)'
	index=0
	while read -r line; do
		IFS=' ' read -r -a array <<< "$line"
		base_value=${array[1]}
		base_threads=${array[0]}
		IFS=' ' read -r -a array <<< "${result_array[$index]}"
		this_value=${array[1]}
        	this_threads=${array[0]}
		RES=`echo "($this_value - ($base_value * $PERF_LIMIT)) > 0 | bc"`
		if [ $RES -ne 1 ]; then
			echo "Sysperf run: $title-$threads failed"
			echo "\t Baseline: $value vs ${array[3]} not within limit"
			PERF_FAILED=1
		fi	
		index=$((index+1))
	done <<< $baseline_res
	
}

# Compare this runs perf to the baseline
function compare_perf {
	cat $BASELINE_FILE | while read -r line
	do
		case $line in
		# Numeric lines are skipped as we want only the header for MongoPerf
		[0123456789]*)
			;;
		">>>*")
			comp_sysperf $line
			;;
		# Anything left should be a mongo-perf header	
		*)
			comp_mongoperf $line
			;;	
		esac		
	done
	if [ $PERF_FAILED -eq 1]; then
		exit 1;
	fi
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
pass_args $@
echo "Performing setup"
rm -rf $LOGDIR
mkdir $LOGDIR

# First we grab all the repos we need to run these tests
get_repos > $LOGDIR/fetch.log
# Now we make MongoDB
#make_mongo > $LOGDIR/make.log

# Gather a baseline for perf analysis
if [ $BASELINE -ne 0 ]; then
	echo "Gathering baseline for Evergreen Runs. This WILL take some time so bare with us"
	if [ -f $BASELINE_FILE ]; then
		cp $BASELINE_FILE $BASELINE_FILE.bkp
	fi
	gather_baseline
fi

# Run the suites, if selected
if [ $LOCAL -ne 0 ]; then
	echo "Starting local worklaods"
	# SERVER-23333 workload
	echo "SERVER-23333"
	cd $MONGODIR
	start_timer
	stdbuf -oL python buildscripts/resmoke.py --executor=no_passthrough_with_mongod $SUITE/SERVER-23333.js --log=file > $LOGDIR/SERVER-23333.log 2>&1
	RES=$?
	end_timer
	if [ $RES -ne 0 ]; then
		echo "Test for SERVER-23333 failed"
		echo "Error(s) from log were:"
		grep "assert failed" $MONGODIR/tests.log
		#exit 1
	fi
	cd $RUNDIR

	# SERVER-20306 workload
	echo "Starting SERVER-20306"
	clean_mongod
	start_mongod
	start_monitor
	cd $MONGODIR
	start_timer
	sh $SUITE/SERVER-20306.sh > $LOGDIR/SERVER-20306.log
	end_timer
	stop_monitor > /dev/null
	check_monitor "SERVER-20306"
	check_mongo
	cd $RUNDIR

	# SERVER-22906 workload
	echo "Starting SERVER-22906"
	clean_mongod
	start_mongod
	start_monitor
	start_timer
	for i in $(seq 1 9); do
		#echo "Launching thread $i" > $LOGDIR/SERVER-22906.log
		$MONGODIR/mongo --quiet $SUITE/SERVER-22906.js &
	done
	$MONGODIR/mongo --quiet $SUITE/SERVER-22906.js
	end_timer
	# Wait for the other threads
	sleep 10
	stop_monitor > /dev/null
	check_mongo
	check_monitor "SERVER-22906"
fi

if [ $YCSB -ne 0 ]; then
	echo "Starting YCSB Workloads"
	# SERVER-24207 workload
	echo "Starting SERVER-24207"
	clean_mongod
	start_mongod
	start_monitor
	start_timer
	load_ycsb $SUITE/SERVER-24207.ycsb > $LOGDIR/SERVER-24207-load.log
	end_timer
	stop_monitor
	check_mongo
	check_monitor "SERVER-24207"

	# Custom smalldoc's workload for this suite
	echo "Starting WT-2669"
	clean_mongod
	start_mongod
	start_monitor
	start_timer
	load_ycsb $SUITE/WT-2669.ycsb > $LOGDIR/WT-2669-load.log
	stop_monitor
	check_monitor "WT-2669-load"
	start_monitor
	check_mongo
	run_ycsb $SUITE/WT-2669.ycsb > $LOGDIR/WT-2669-run.log
	end_timer
	stop_monitor
	check_mongo
	check_monitor "WT-2669-run"
fi

if [ $EVG -ne 0 ]; then
	if [ ! -f $BASELINE_FILE ]; then
		echo "No baseline file available. Please run '$0 --baseline' to gather one"
		echo "Without a baseline, there can be no comparison. Exiting"
		exit 0;
	fi
	echo "Starting Evergreen Workloads"
	echo "Starting a mongo-perf run"
	# mongo-perf run
	clean_mongod
        start_mongod
        start_timer
	cd $RUNDIR/mongo-perf
	stdbuf -oL python benchrun.py --shell $MONGODIR/mongo -t 1 8 --trialCount 1 \
                -f testcases/*.js --includeFilter insert misc update query \
                --includeFilter core regression --excludeFilter single_threaded \
                --out $LOGDIR/perf.json --exclude-testbed > $LOGDIR/mongo-perf.log 2>&1
	cd $RUNDIR
	end_timer
	check_mongo

	echo "Starting a sys-perf run"
	clean_mongod
        start_mongod
        start_timer
	cd $RUNDIR/workloads
#	stdbuf -oL python run_workloads.py --shell $MONGODIR/mongo -w $SYSPERF_WORKLOADS > $LOGDIR/sys-perf.log
	cd $RUNDIR
        end_timer
        check_mongo
	egrep -v "Finished|mongoPerf|version|connecting|load|^$|`cd $MONGODIR; git show-ref -s | head -n1; cd ..`" $LOGDIR/mongo-perf.log > $RUN_PERF_FILE
        egrep ">>>" $LOGDIR/sys-perf-baseline.log >> $RUN_PERF_FILE
	compare_perf
fi
