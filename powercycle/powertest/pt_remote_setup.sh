#!/bin/bash

source ./pt_config


echo "About to run setup"

# installMongoDB urlOfTarball installDir
# Downloads urlOfTarball and installs in home directory mongodb
# If urlOfTarball is a directory on the host, skip download and create link
# Return directory path of bin directory
function installMongoDB {
  urlOfTarball=$1
  installDir=$2
  if [ $# -ne 2 ]; then
    urlOfTarball="http://fastdl.mongodb.org/linux/mongodb-linux-x86_64-latest.tgz"
    installDir="$(pwd)/mongodb-$(date +%s)"
  fi
  mkdir $installDir
  # directory for mongodb supplied instead of url, create link
  if [ -d $urlOfTarball ]; then
    ln -s $urlOfTarball $installDir/bin
  else
    wget --quiet $urlOfTarball
    tarball=${urlOfTarball##*/}
    tar -xzf $tarball -C $installDir
    rm $tarball
  fi
  echo $(find -L $installDir -name bin -type d)
}

if [ -d "$remoteRunDir" ]; then
  echo "Run directory already exists, clearing out for setup"
  rm -rf $remoteRunDir
fi

bindir=$(installMongoDB $dlUrl $tmpDir)

# Create data & log directories
echo "Creating working directories $dataDir $mlogDir"
mkdir -p $mdataDir $mlogDir $mbackupDir

# Now startup the server to make sure we can create a database.

logPath=$mlogDir/mongod-${storageEngine}.log
startMongod $secretPort $logPath

# Shutting down mongod server.
shutdownMongod localhost $secretPort

