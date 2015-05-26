#!/bin/bash

source pt_config

# Setup a local directory where we can find mongo command(s)
if [ "x$localBinDir" != "x" ]; then
  if [ ! -e $localBinDir/mongo ]; then
    echo "$0: mongo binary not found in $localBinDir"
    exit 1
  fi
  bindir=$localBinDir
else
  mongoExe=`which mongo`
  bindir=`dirname $mongoExe`
fi

if [ "x$bindir" = "x" ]; then
  echo "$0: Could not find mongo binaries in path. Done."
  exit 2
fi

# mongoClient hostUrl hostPort
# Executes CRUD operations on mongo shell
function mongoClient {
  _hostUrl=$1
  _hostPort=$2

  echo "Starting $bindir/mongo"
  $bindir/mongo --host $_hostUrl --port $_hostPort <<EOF

    use test;

    var baseNum = 10000;
    var coll = db.foo;

    //coll.drop();
    coll.ensureIndex({x: 1});
    var largeValue = new Array(1024).join('Largevalue');
    var res;
    while (true) {
      print();
      print(Date());
      try {
        var info = db.hostInfo();
        var serverStatus = db.serverStatus();
        print("dbHostInfo status:", info.ok, serverStatus.version,
              "storageEngine:", serverStatus.storageEngine.name,
              "uptime:", serverStatus.uptime);
        var op = Math.floor(Math.random() * 10) % 10;
        var match = Math.floor(Math.random() * 1000000) % baseNum;
        switch(op) {

            case 0:
            case 1:
                // bulk insert baseNum docs
                print("Bulk insert", baseNum, "docs");
                var bulk = coll.initializeUnorderedBulkOp();
                    for (var i = 0; i < baseNum; i++) {
                        bulk.insert({x: i, doc: largeValue});
                    }
                res = bulk.execute();
                printjson(res);
                break;

            case 2:
            case 3:
                // update docs
                print("Upsert docs");
                res = coll.update(
                    {x: {\$gte: match}},
                    {\$inc: {x: baseNum}, \$set: {n: "hello"}},
                    {upsert: true, multi: true});
                printjson(res);
                break;

            case 4:
                // Create a new collection then drop it.
                print("New collection ops");
		var random_name =  (0|Math.random()*9e6).toString(36);
		res = db.createCollection(random_name);
		new_coll = db.getCollection(random_name);
		new_coll.ensureIndex({x : 1});
		// Add some content.
		var bulk = new_coll.initializeUnorderedBulkOp();
		    for (var i = 0; i < baseNum; i++) {
			bulk.insert({x: i, doc: largeValue});
		    }       
		res = bulk.execute();
		printjson(res);
		print("Find docs");
                res = new_coll.find({x: {\$gte: match}}).count();
		new_coll.drop();
                break;
            case 5:
            case 6:
            case 7:
            case 8:
                // find matchings docs
                print("Find docs");
                res = coll.find({x: {\$gte: match}}).count();
                printjson(res);
                break;

            case 9:
                // remove matching docs
                print("Remove docs");
                res = coll.remove({x: {\$gte: match}});
                printjson(res);
                break;

        }
        res = coll.count();
        print("Docs in collection", res);
        //res = coll.validate({full:true}).ok;
        //print("Validate collection: ", res);
        //sleep(500);
      } catch(e) {
        print("Error encountered", tojson(e));
        sleep(10000);
      }
    }
  }
EOF
}

# startClients numClients rootDir hostPort
function startClients {
  _numClients=$1
  _hostUrl=$2
  _hostPort=$3

  for i in $(seq 1 $_numClients)
  do
    # Run in background
    mongoClient $_hostUrl $_hostPort > /dev/null &
  done
}

# crashSeverLXC
function crashServerLXC {
  sudo echo "Server crashing now!"
  lxcPid=`pidof lxc-start`
  if [ $lxcPid ]; then
    sudo kill -9 $lxcPid
  fi
  #sudo lxc-stop -n $lxcContainer -W -k
}

# waitForRandomTime base variance
function waitForRandomTime {
  secs=$1
  variance=$2
  if [ $# -ne 2 ]; then
    secs=30
    variance=5
  fi
  x=$(((RANDOM % ($variance))+$secs))
  echo "Waiting for random time: $x"
  sleep $x
}

function startServerLXC {
  isRunning=`sudo lxc-ls -f | grep crashme | grep RUNN`
  if [ "x$isRunning" = "x" ]; then
    sudo lxc-start -n $lxcContainer -d
  fi
}

function runOneCycle {
  echo "Starting remote machine if required."
  startServerLXC

  echo "Connecting to remote machine and getting the server running"
  $sshCmd $sshHostConnection \
    "cd $remoteTestDir; \
    bash pt_remote_run.sh"

  if [ $? -ne 0 ]; then
    echo "$0: Error recovering or starting mongod on remote machine"
    exit 1
  fi

  echo "Starting $numClients local shells doing operations on mongod"
  startClients $numClients $sshHost $standardPort

  waitForRandomTime $runTimeBase $runTimeVariance
  crashServerLXC

  # Stop the mongo shells we created.
  myProcs=`jobs -p`
  mongoProcs=`pidof mongo`
  echo "About to kill child processes: $mongoProcs $myProcs"
  echo $mongoProcs $myProcs | xargs kill > /dev/null
}

crashServerLXC

loops=0
while true; do
  echo "######################################################"
  echo "######################################################"
  echo "Running crash test, cycle $loops"
  runOneCycle
  loops=`expr $loops + 1`
done
