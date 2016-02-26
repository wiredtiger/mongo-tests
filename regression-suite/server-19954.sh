#!/bin/bash

# -> Start Mongo

    (
        # insert on 20 threads in parallel into a total of 50k collections
        for t in $(seq 5); do
            ./mongo --quiet --eval "
            (function (t, n) {
                for (var i=0; i<n; i++) {
                    c = db['c'+t+'.'+i]
                    c.insert({})
                    if (i%100==0)
                        print(t,i)
                }
            })($t,2500);
            " &
        done
        wait
    )

./mongostat > mongostat.out &
KILL_PID=$!
 
# now try to insert some data to make stall evident
(
    for t in $(seq 20); do
        ./mongo --quiet --eval "
        (function () {
        count = 1000000
        every = 10000
        for (var i=0; i<count; ) {
            var bulk = db.c.initializeUnorderedBulkOp();
            for (var j=0; j<every; j++, i++)
                bulk.insert({})
                bulk.execute();
                print(i)
            }
        })();
        " &
    done
    wait
)

kill $KILL_PID
RES=`tail -n +3 mongostat.out | head -n -1 | awk '{print $1}' | grep '\*0' | wc -l`
if [ $RES -gt 1 ]; then
    echo "We saw some stalls (0 throughput per second)"
    exit 1
fi

# -> Stop Mongo
