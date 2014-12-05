#!/bin/sh
: ${MONGODB_BIN:?"Please set MONGODB_BIN to path for MongoDB binaries"}

rm -r db
mkdir -p db/s0r0
mkdir -p db/s1r0
mkdir -p db/c

$MONGODB_BIN/mongod --dbpath ./db/s0r0 --logpath ./db/s0r0.log --logappend --port 30000  --storageEngine wiredtiger --fork
$MONGODB_BIN/mongod --dbpath ./db/s1r0 --logpath ./db/s1r0.log --logappend --port 31000  --storageEngine wiredtiger --fork
$MONGODB_BIN/mongod --configsvr --dbpath db/c --logpath db/c.log --logappend --fork
$MONGODB_BIN/mongos --port 27017 --configdb localhost --logpath db/ms0.log --logappend  --noAutoSplit --fork


