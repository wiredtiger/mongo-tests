#!/bin/bash
if [ $# -eq 0 ]
  then
    echo "No dbpath supplied"
    echo "Usage ./runner.sh dbpath"
    exit 1
fi

rm -rf $1
mkdir $1
./build/install/bin/mongod --config=config
sleep 5
./build/install/bin/mongo --eval "rs.initiate()"
