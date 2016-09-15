threads=10
gb=8
function make {
    cn=$1
    (
        for t in $(seq $threads); do
            mongo --eval "
                c = db['$cn']
                c.createIndex({a:1})
                c.createIndex({b:1})
                c.createIndex({c:1})
                every = 10000
                for (var i=0; c.stats().size < $gb*1000*1000*1000; i++) {
                    var bulk = c.initializeUnorderedBulkOp();
                    for (var j=0; j<every; j++, i++)
                        bulk.insert({a:i, b:i, c:i})
                    bulk.execute();
                    if ($t==1)
                        print(c.stats(1024*1024).size)
                }
            " &
        done
        wait
    )
}

# scan a collection to load it
function load {
    cn=$1
    mongo --eval "
        c = db['$cn']
        print(c.find({x:0}).itcount())
    "
}

make ping >> results.txt  # generate a 10 GB collection
make pong >> results.txt  # generate another 10 GB collection
sleep 120  # sleep a bit to wait for writes; makes stats clearer
load ping >> results.txt # scan first 10 GB collection to load it back into cache
