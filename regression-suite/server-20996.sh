function insert {
    threads=24
    for t in $(seq $threads); do
        ./mongo --eval "
            count = 100000
            every = 10000
            for (var i=0; i<count; ) {
                var bulk = db.c.initializeUnorderedBulkOp();
                for (var j=0; j<every; j++, i++)
                    bulk.insert({})
                bulk.execute();
                print(i)
            }
        " &
    done
    wait
}
 
function remove {
 
    ./mongo --quiet --eval "
        t = new Date()
        db.c.remove({})
        t = new Date() - t
        print(t/1000.0)
    "
}

# -> Start MongoD here 
insert;
RES=`time remove`
#-> stop MongD here
if [ 1 -eq "$(echo "${RES} > 60" | bc)" ];
then
	echo "Took more than 60 seconds to run test"
	exit 1	
fi

