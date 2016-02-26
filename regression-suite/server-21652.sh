#!/bin/bash

# -> Start mongo replset, 10gb cache 10gb ioplog

t=15

./mongostat > mongostat.out &
KILL_PID=$!

./mongo --quiet --eval "
(function (threads) {
 
    Random.setRandomSeed();
 
    db.c.ensureIndex({y:1})
 
    var docs = [];
    for (var i = 0; i < 1000; i++) {
        var x = '';
        while (x.length < 1000)
            x += 'x'
        docs.push({x: x, y: i, z: 0});
    }
 
    var insert_ops = [{
        op: 'insert',
        ns: 'test.c',
        doc: docs,
        safe: true,
    }];
 
    var res = benchRun({
        ops: insert_ops,
        seconds: 10000,
        parallel: threads
    });
    printjson(res);
 
})($t);"

kill $KILL_PID
# -> stop mongod
RES=`tail -n +3 mongostat.out | head -n -1 | awk '{print $1}' | grep '\*0' | wc -l`
if [ $RES -gt 1 ]; then
    echo "We saw some stalls (0 throughput per second)"
    exit 1
fi
