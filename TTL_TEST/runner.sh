#!/bin/bash
if [ $# -eq 0 ]
  then
    echo "No dbpath supplied"
    echo "Usage ./runner.sh dbpath"
    exit 1
fi

rm -rf $1
mkdir $1
./build/install/bin/mongod --dbpath=$1 --wiredTigerCacheSizeGB=1 --setParameter ttlMonitorSleepSecs=15
#db.adminCommand({setParameter:1, ttlMonitorSleepSecs:2})
#internalQueryExecYieldIterations
