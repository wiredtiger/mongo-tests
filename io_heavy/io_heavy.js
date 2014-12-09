load("../lib/parallelTester.js");

db_name = "io_heavy";
var object_size = 50;
var total_objects = 2*Math.pow(10, 6);
var num_insert_threads = 10;
var num_update_threads = 10;
var wait_for_insert = true;

var insert_chunk = Math.floor(total_objects/num_insert_threads);
var update_chunk = Math.floor(total_objects/num_update_threads);

function insert_thread(db_name, thread, count, show, padding){
    var seed = thread + 1;
    function randomArray(len) {
        var rv = new Array(len);
        while (--len >= 0) {
            var x = Math.sin(seed++) * 10000;
            rv[len] = x - Math.floor(x);
        }
        return rv;
    }    

    issue_db = connect(db_name)
    every = 1000;
    if(count < every){every = count;}
    var t = new Date()
    for (var i=0; i<count; ) {
        var bulk = issue_db.c.initializeUnorderedBulkOp();
        for (var j=0; j<every; j++, i++)
            bulk.insert({_id :thread*count + i, "val" :  i, "padding" : randomArray(padding)})
        bulk.execute();
        if (thread%show==0) {
            var tt = new Date()
            print("insert:", tt, thread, show, i, Math.floor(every / (tt-t) * 1000))
            t = tt
        }
    }
}

function update_thread(db_name, thread, count, show, object_size) {
    issue_db = connect(db_name)
    padding  = new Array(object_size - 30).join("a");
    every = 1000;
    if(count < every){every = count;}
    var t = new Date()
    for (var i=0; i<count; ) {
        var bulk = issue_db.c.initializeUnorderedBulkOp();
        for (var j=0; j<every; j++, i++)
            bulk.find({_id : thread*count + i}).updateOne({$set : {val : "X"}});
        bulk.execute();
        if (thread%show==0) {
            var tt = new Date()
            print("update:", tt, thread, show, i, Math.floor(every / (tt-t) * 1000))
            t = tt
        }
    }
}

connect(db_name).dropDatabase();

print("Inserting " + insert_chunk + " object per thread in " + num_insert_threads + " threads")
insert_threads = [];
for (var i = 0; i < num_insert_threads; ++i) { 
   var t = new ScopedThread(insert_thread, db_name, i, insert_chunk, 10, object_size); 
   insert_threads.push(t); 
   t.start() 
}

if(wait_for_insert == true){
	for (var i in insert_threads) { var t = insert_threads[i]; t.join();} 
}

var start = new Date()
update_threads = [];
for (var i = 0; i < num_update_threads; ++i) { 
   var t = new ScopedThread(update_thread, db_name, i, update_chunk, 10, object_size); 
   update_threads.push(t); 
   t.start() 
}
  
if(wait_for_insert == true){
	for (var i in update_threads) { var t = update_threads[i]; t.join();} 
} else {
	for (var i in insert_threads) { var t = insert_threads[i]; t.join();} 
	for (var i in update_threads) { var t = update_threads[i]; t.join();}
}

var end = new Date()
print(total_objects,end - start)
print("done..."); 



