#!/bin/bash

source pt_config

bindir=$(getBinDir .)

# Verify that a database directory exists.

if [ ! -d $mdataDir ]; then
  echo "$0: Attempting to run test without setting up first."
  exit 1
fi

# If there is a mongod running, the system didn't crash, so we aren't
# in the state we expected.
numProcessRunning mongod
if [ $? != 0 ]; then
  echo "$0: Attempting to do recovery test while mongod is still running"
  exit 4
fi

# Backup the directory.
$rsyncCmd $mdataDir $mbackupDir/before_recovery

# Start on port 37017 and let recovery run.
logPath=$mlogDir/mongod-${storageEngine}-recovery.log
startMongod $secretPort $logPath

# Run validate on the mongod.
validate="print(tojson(db.serverStatus()), tojson(db.foo.validate(true)))"
connectToMongod localhost $secretPort "$validate"
if [ $? -ne 0 ]; then
  echo "$0: Failed to validate database after recovery."
  exit 2
fi

# Shutdown on 37017
shutdownMongod localhost $secretPort

# Backup the directory.
$rsyncCmd $mdataDir $mbackupDir/after_validate

# Start server on 27017
logPath=$mlogDir/mongod-${storageEngine}.log
startMongod $standardPort $logPath

# Verify that the server is running
countDocs="print(tojson(db.hostInfo()), 'docs in db.foo:', db.foo.count())"
connectToMongod localhost $standardPort "$countDocs"
if [ $? -ne 0 ]; then
  echo "$0: Could not connect to mongod after recovery"
  exit 3
fi
