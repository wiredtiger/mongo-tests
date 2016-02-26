#!/bin/bash
function create {
    ./mongo --eval "db.createCollection('c')"
    ./mongo --eval "db.c.createIndex({x:1})"
}
 
function insert {
    threads=24
    for t in $(seq $threads); do
        ./mongo --eval "
            count = 200000
            every = 10000
            for (var i=0; i<count; ) {
                var bulk = db.c.initializeUnorderedBulkOp();
                for (var j=0; j<every; j++, i++)
                    bulk.insert({x:i})
                bulk.execute();
                print(i)
            }
        " &
    done
    wait
}
 
function remove {
    ./mongo --eval "db.c.remove({})"
}
 
function update {
    threads=4
    for t in $(seq $threads); do
        ./mongo --quiet --eval "
            count = 200000
            every = 10000
            t = new Date()
            for (var i=0; i<count; ) {
                var bulk = db.c.initializeUnorderedBulkOp();
                q = {x: 0}
                u = {\$inc:{y:1}}
                for (var j=0; j<every; j++, i++)
                    bulk.find(q).update(u)
                bulk.execute();
            }
        " > /dev/null &
    done
    wait
}

# -> Start mongod
 
create > /dev/null;
before=$( { time update; } 2>&1 )
before=$(echo "$before" | grep real | awk -F m '{print $2}' | sed 's/s//')
insert > /dev/null;
remove > /dev/null;
after=$( { time update; } 2>&1 )
after=$(echo "$after" | grep real | awk -F m '{print $2}' | sed 's/s//')

# -> stop mongod

echo "Comparing first run $before to $after"
if [ 1 -eq $(echo "$after > $before * 1.5" | bc) ];
then
	echo "We took far longer for the second run - $after vs $before"
	exit 1
fi

