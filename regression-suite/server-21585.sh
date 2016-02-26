#!/bin/bash

#-> Start Mongod (one node replset 50KB oplog, nojournal)

./mongostat > mongostat.out &
KILL_PID=$!

./mongo --quiet --eval "
(function() {
    'use strict';
 
    Random.setRandomSeed();
 
    var docs = [];
    for (var i = 0; i < 1000; i++) {
        var x = '';
        while (x.length < 1000) {
            x += Random.rand();
        }
        docs.push({x: x});
    }
    var ops = [{
        op: 'insert',
        ns: 'test.c',
        doc: docs,
        safe: true,
    }];
    var res = benchRun({
        ops: ops,
        seconds: 10000,
        parallel: 5
    });
    printjson(res);
 
    rst.stopSet();
})();
"
kill $KILL_PID
# -> Stop Mongod
RES=`tail -n +3 mongostat.out | head -n -1 | awk '{print $1}' | grep '\*0' | wc -l`
if [ $RES -gt 0 ];
then
        echo "Failed as we 0 throughput for $RES second(s)"
        exit 1;
fi
