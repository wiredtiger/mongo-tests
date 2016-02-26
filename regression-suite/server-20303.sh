counts="1 2 4 8 16"
seconds=30
dbpath="/mnt/work/data"

echo "" > output.log
last=0
fail=0
 
for threads in $counts; do
# -> Clean Mongod (--nojournal --syncdelay 0 --oplogSize 1000000)
    pkill -9 mongod
    sleep 2
    rm -rf /data/db/*
    sleep 2
    ./mongod --fork --dbpath $dbpath --logpath $dbpath.log --nojournal --syncdelay 0 --oplogSize 1000000 > /dev/null
    sleep 6
    RES=`./mongo --quiet --eval "
        x = ''
        for (var i=0; i<100000; i++)
            x += 'x'
        printjson(benchRun({
            ops: [{
                op: 'insert',
                ns: 'test.c',
                doc: {x:x},
                //safe: true,
            }],
            seconds: $seconds,
            parallel: $threads
        }))
    "`
    echo "$RES" >> output.log
    FINAL=`echo -e "$RES" | grep insert\" | awk '{print $3}' | sed 's/,//g'`
    echo "$threads $FINAL"
    if [ 1 -eq "$(echo "${FINAL} < ${last} * 1.5" | bc)" ]; then
        echo "Didn't see the required increase between $(echo "${threads}/2" | bc) and $threads threads"
        echo "Test was $FINAL > $(echo "${last} * 1.5" | bc)"
        fail=1
    fi
    last=$FINAL
done
# -> terminate mongod
if [ $fail -eq 1 ]; then
	exit 1
fi
