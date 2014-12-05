load("../lib/parallelTester.js");

function insert_thread(db_name, thread, show) {
    issue_db = connect(db_name)
    count = 100000
    every = 1000
    var t = new Date()
    for (var i=0; i<count; ) {
        var bulk = issue_db.c.initializeUnorderedBulkOp();
        for (var j=0; j<every; j++, i++)
            bulk.insert({})
        bulk.execute();
        if (thread%show==0) {
            var tt = new Date()
            print(tt, thread, show, i, Math.floor(every / (tt-t) * 1000))
            t = tt
        }
    }
}

function run_16355(num_threads) {
    db_name = "16355";
    connect(db_name).dropDatabase();
    connect(db_name).setProfilingLevel(1,5000);
    threads = [];
    for (var i = 0; i < num_threads; ++i) { 
        var t = new ScopedThread(insert_thread, db_name, i, 20); 
        threads.push(t); 
        t.start() }

    for (var i in threads) { var t = threads[i]; t.join(); }  
    print("done..."); 
}


run_16355(100);

