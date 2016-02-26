#!/bin/bash

#-> Setup MongoD Here

if [ "$1" == "" ]; then
	THREADS=5	
else
	THREADS=$1
fi
if [ "$2" == "" ]; then
	WRITECMD=true
else
	WRITECMD=$2
fi
if [ "$3" == "" ]; then
	MULTI=false
else
	MULTI=$3
fi
if [ "$4" == "" ]; then
    BENCH_SECONDS=120
else
    BENCH_SECONDS=$4
fi
COLLECTIONS=8
VECTOR_SIZE=100
DOCUMENT_SIZE=512
MONGO=./mongo

# x = benchRun( { ops: [{op: "insert", ns: "test.repro" + threads, doc: {_id: {"#OID":1} } } ], parallel: threads, seconds: '$BENCH_SECONDS', writeCmd: true } ).insert

# This ensures that the replica set is up and running, and we're not measuring the time to
# create the collection etc
$MONGO --quiet -eval '
    db.dropDatabase()
    collections = '$COLLECTIONS'
    for (i = 1; i <= collections; i++) {
        t = eval("db.repro"+i)
        result = t.insert({x:1}, {w:"majority"})
        result = t.remove({}, {w:"majority"})
    }
'

# Setup and fork out mongostat
./mongostat > mongostat.out &
KILL_PID=$!

$MONGO --quiet -eval '
function makeDocument(docSize) {
    var doc = { _id: {"#OID":1}, "fieldName":"" };
    while(Object.bsonsize(doc) < docSize) {
        doc.fieldName += "x";
    }
    return doc;
}

threads='$THREADS'
singledoc = makeDocument('$DOCUMENT_SIZE')
singledoc_noid = Object.extend({}, singledoc, true)
delete singledoc_noid._id

if ("'$MULTI'" == "true") {
    doc = []
    for (i = 0; i < '$VECTOR_SIZE'; i++) {
        doc.push(singledoc)
    }
} else {
    doc = singledoc
}
collections = '$COLLECTIONS'
ops = []
for (i = 1; i <= collections; i++) {
    eval("db.repro"+i).drop()
    ops.push({op: "insert", ns: "test.repro"+i, doc: doc, writeCmd: '$WRITECMD'})
}

args = { ops: ops, parallel: threads, seconds: '$BENCH_SECONDS' }
insertsPerSecond = benchRun(args).insert

totalRecords = 0
for (i = 1; i <= collections; i++) {
    t = eval("db.repro"+i)
    findOne = t.findOne({}, {_id:0})
    if (JSON.stringify(findOne) != JSON.stringify(singledoc_noid)) {
        print("ERROR doc does not match intended:")
        print(JSON.stringify(findOne))
    }
    totalRecords += t.count()
}

if( Object.prototype.toString.call( doc ) === "[object Array]" ) {
    insertsPerSecond *= doc.length
}

output = threads + ":" + Math.round(insertsPerSecond) + " " + totalRecords / '$BENCH_SECONDS'
print(output)
' | tee -a ~/benchRun.log

kill $KILL_PID
#-> teardown mongod here

# Check how many seconds we saw 0 throughput for according to mongostat.
# We trim the first 2 lines and last line, as they may contain 0's while the
# test starts up.
RES=`tail -n +3 mongostat.out | head -n -1 | awk '{print $1}' | grep '\*0' | wc -l`
if [ $RES -gt 0 ];
then
	echo "Failed as we 0 throughput for $RES second(s)"
	exit 1;
fi
exit 0;

