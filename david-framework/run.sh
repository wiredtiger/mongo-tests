#!/bin/bash

DBPATH=/data/db
TOP_DIR=`pwd`
SUITE_DIR=$TOP_DIR/suites
MONGO_DIR=$TOP_DIR/mongo
SUITES=`ls $SUITE_DIR`
MODE="existing"
RUNS_DIR=$TOP_DIR/runs
RUN_DIR=""
RUN_OVERRIDE=""


function do_help 
{
	echo "$0 --suites=<suites> --mongo=[compile|<url>|existing]"
	exit 0
}

function setup_mongo
{
	RET=0
	if [ $1 != "existing" ]; then 
		rm -rf $MONGO_DIR
	fi
	if [ $1 == "compile" ]; then
		git clone http://github.com/mongodb/mongo
		cd $MONGO_DIR
		scons -j10 core --disable-warnings-as-errors
		cd $TOP_DIR
	fi
	if [ $1 == "http*" ]; then
		wget $1 -O mongo.tgz
		mv mongo.tgz $MONGO_DIR
		cd $MONGO_DIR
		tar -xzvf mongo.tgz
		rm mongo.tgz
		MONGODIR=$RUNDIR/`ls |grep mongo*`
		mv $MONGODIR/bin/* $MONGO_DIR
		
	fi
	if ! [ -f $MONGO_DIR/mongo ]; then
		echo "Error, no mongo shell found in $MONGO_DIR"
		RET=1
	fi
	if ! [ -f $MONGO_DIR/mongod ]; then
		echo "Error, no mongod found in $MONGO_DIR"
		RET=1
	fi
	if [ $RET -ne 0 ]; then
		exit
	fi
}

function stop_mongo
{
        killall -q -9 mongod 2>&1 > /dev/null
}

function post_run
{
	cd $TOP_DIR
	sleep 5	
	stop_mongo
	sleep 5
        # Save diag.data
	mv $DBPATH/diagnostic.data $RUN_DIR
        rm -rf $DBPATH
	mkdir $DBPATH
}

function start_mongo
{
        SUITE=$1
        if [ -f $SUITE_DIR/$SUITE/mongod.conf ]; then
                $MONGO_DIR/mongod --dbpath $DBPATH --logpath $RUN_DIR/mongod.log --fork  -f $SUITE_DIR/$SUITE/mongod.conf
        else
                $MONGO_DIR/mongod --dbpath $DBPATH --logpath $RUN_DIR/mongod.log --fork
        fi
}

## MAIN
# Argument processing
for var in "$@"
do
	case $var in
	
	--suites=*)
		SUITES=`echo $var|awk -F= '{print $2}'| sed 's/,/ /g'`
	;;

	--mongo*)
		MODE=`echo $var|awk -F= '{print $2}'`
	;;
	--runname*)
		RUN_OVERRIDE=`echo $var|awk -F= '{print $2}'`
	;;
	--help)
		do_help
	;;
	esac
done

stop_mongo

if ! [ -d $RUNS_DIR ]; then
	mkdir $RUNS_DIR
fi
if [ -d $DBPATH ]; then
	rm -rf $DBPATH
fi
mkdir $DBPATH
setup_mongo $MODE

# If we're naming the run, use that here
if [ $RUN_OVERRIDE == "" ]; then
	RUNS_DIR="$RUNS_DIR/`date '+%Y%m%d-%H%M%S'`"
else
	RUNS_DIR="$RUNS_DIR/$RUN_OVERRIDE"
fi

mkdir $RUNS_DIR
for suite in $SUITES
do
	RUN_DIR="$RUNS_DIR/$suite"
	mkdir $RUN_DIR
	cd $RUN_DIR
	start_mongo $suite
	echo "Running: $suite"
	#run suite
	export PATH=$MONGO_DIR:$PATH
	bash $SUITE_DIR/$suite/run.sh
	post_run
done

