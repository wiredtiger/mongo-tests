load("../lib/parallelTester.js");

function insert_thread(thread) {
    var seed = thread + 1;
    function randomString(len) {
        var rv = "";
        while (len >= 0) {
            var x = Math.sin(seed++) * 10000;
            rv += (x - Math.floor(x));
            len -= 20;
        }
        return rv;
    }
    
    count = 10000000
    every = 1000
    var t = new Date()
    for (var i=0; i<count; ) {
        var bulk = db.c.initializeUnorderedBulkOp();
        for (var j=0; j<every; j++, i++){
            bulk.insert({"payload" : randomString(500)});
        }
        bulk.execute();
    }
}

function reader_thread(total){
    var tCursor = db.c.find().addOption(DBQuery.Option.tailable).
                      addOption(DBQuery.Option.awaitData);
    count = 0;
    while (count < total) {
      if(tCursor.hasNext()){
          var doc = tCursor.next();
          if(++count % 100000 == 0){
              print("read:", (new Date()).toLocaleTimeString(), count, db.c.stats().wiredTiger.btree["maximum tree depth"]);
          }
      } else {
        sleep(1000);   
      }
   }  
   print("reader done...");  
};


function run_16697(num_threads) {
    db.c.drop();
    db.createCollection("c", { capped: true, size: 10000000000 } );
    db.c.insert({});
    threads = [];
    for (var i = 0; i < num_threads; ++i) { 
        var t = new ScopedThread(insert_thread, i); 
        threads.push(t); 
        t.start() }
    var reader = new ScopedThread(reader_thread, 100000000);
    threads.push(reader);
    reader.start();
    for (var i in threads) { var t = threads[i]; t.join(); }  
    print("done..."); 
}

run_16697(100);

