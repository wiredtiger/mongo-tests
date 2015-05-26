#!/bin/bash

_tmpTar=_pt.tgz

# Setup the config parameters
source ./pt_config

# Get a copy of our files:
rm -f $_tmpTar && tar zcf $_tmpTar "./"

if [ "$1" = "--force" ]; then
  $sshCmd $sshHostConnection \
    "rm -rf $remoteTestDir"
fi
# Get our archive onto the remote machine
rsync -av -e "ssh $sshSetup" $_tmpTar $sshHost:$remoteTestDir/

# Unpack the scripts on the remote machine
echo "Connecting to remote machine and running setup step."
$sshCmd $sshHostConnection \
  "cd $remoteTestDir; \
  tar zxf $_tmpTar; \
  bash -x ./pt_remote_setup.sh"
