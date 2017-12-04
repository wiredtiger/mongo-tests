// Insert large docs as fast as possible across multiple threads.

load("../lib/parallelTester.js");

function insert_thread(db_name, thread, show) {
    issue_db = connect(db_name)
    count = 1000000
    every = 1
    var x = "1234567890";
    var iterations = 8; // 10 * 3 ^ iterations = 65610 at 8, 19683 at 9
    for (var i = 0; i < iterations; i++) {
        x += x.concat(x);
    }
    var t = new Date()
    for (var i=0; i<count; count++) {
        issue_db.c.insert( { field : x } )
        if (count%show==0) {
            var tt = new Date()
            print(tt, thread, show, i, Math.floor(every / (tt-t) * 1000))
            t = tt
        }
    }
}

function run_32139(num_threads) {
    db_name = "32139";
    connect(db_name).dropDatabase();
    threads = [];
    for (var i = 0; i < num_threads; ++i) { 
        var t = new ScopedThread(insert_thread, db_name, i, 10000);
        threads.push(t); 
        t.start() }

    for (var i in threads) { var t = threads[i]; t.join(); }  
    print("done..."); 
}


run_32139(5);

