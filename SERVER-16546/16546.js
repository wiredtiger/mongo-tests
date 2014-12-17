load("../lib/parallelTester.js");

function insert_thread(db_name, thread, show) {
    var seed = thread + 1;
    function randomString(len) {
        var rv = "";
        while (len > 0) {
            var x = Math.sin(seed++) * 10000;
            rv += (x - Math.floor(x));
            len -= 20;
        }
        return rv;
    }
    
    issue_db = connect(db_name)
    count = 10000000
    every = 1000
    var t = new Date()
    for (var i=0; i<count; ) {
        var bulk = issue_db.c.initializeUnorderedBulkOp();
        for (var j=0; j<every; j++, i++){
            var id = "user_" + thread + "_" + i;
            bulk.insert({"_id" : randomString(100), "payload" : randomString(1000)});
        }
        bulk.execute();
        if (thread%show==0) {
            var tt = new Date()
            print(tt, thread, show, i, Math.floor(every / (tt-t) * 1000))
            t = tt
        }
    }
}

num_threads = 10;
db_name = "16546";
connect(db_name).dropDatabase();
threads = [];
for (var i = 0; i < num_threads; ++i) { 
    var t = new ScopedThread(insert_thread, db_name, i, 20); 
    threads.push(t); 
    t.start() }

for (var i in threads) { var t = threads[i]; t.join(); }  
print("done..."); 

