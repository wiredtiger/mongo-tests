function producer(db_name, producer) {
    var issue_db = connect(db_name)
    var count = 100000
    var limit = 10000
    var every = 1000
    for (var i=0; i<count; i++) {
        issue_id = producer*count + i;
        issue_db.c.insert({_id:issue_id})
        if (i>0 && i%every==0) {
            c = issue_db.c.count()
            print('pro', i, issue_db.c.count())
            while (c>limit) {
                sleep(100)
                c = issue_db.c.count()
            }
        }
    }
}
 
function consumer(db_name, worker) {
    var issue_db = connect(db_name)
    var count = 100000
    var every = 1000
    var t = new Date()
    for (var i=0; i<count; i++) {
        doc = issue_db.c.findAndModify({query: {worker: null}, update: {$set: {worker: worker}}})
        if (doc) {
            issue_db.c.remove(doc)
        }  else {
            sleep(100)
        }
        if (i>0 && i%every==0) {
            var tt = new Date()
            print('worker', worker, i, Math.floor(every/(tt-t)*1000))
            t = tt
        }
    }
}

function run_consumers(num_threads) {
    db_name = "16296";
    connect(db_name).dropDatabase();
    connect(db_name).setProfilingLevel(1,5000);
    threads = [];
    for (var i = 0; i < num_threads; ++i) {
        var t = new ScopedThread(consumer, db_name, i);
        threads.push(t);
        t.start() }

    for (var i in threads) { var t = threads[i]; t.join(); }
    print("done consuming...");
}

function run_producers(num_threads) {
    db_name = "16296";
    threads = [];
    for (var i = 0; i < num_threads; ++i) {
        var t = new ScopedThread(producer, db_name, i);
        threads.push(t);
        t.start() }

    for (var i in threads) { var t = threads[i]; t.join(); }
    print("done producing...");
}


