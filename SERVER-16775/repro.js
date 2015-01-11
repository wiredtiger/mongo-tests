function create(size) {
    db.createCollection("c", {capped: true, size: size})
}
      
function insert(count) {
    var every = 10000
    var bulk = db.c.initializeUnorderedBulkOp();
    var t = new Date()
    for (var i=0; i<=count; i++) {
        if (i>0 && i%every==0) {
            bulk.execute();
            bulk = db.c.initializeUnorderedBulkOp();
            tt = new Date()
            print(i, Math.floor(every / (tt-t) * 1000))
            t = tt
        }
        bulk.insert({})
    }
}
  
db_name = "16775";
db = connect(db_name);
db.dropDatabase();
create(10000000)
insert(100000000)
