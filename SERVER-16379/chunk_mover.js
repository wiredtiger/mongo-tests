function test(count) {
 
    // insert one document in chunk _id<0
    // this ensures deletes when we move the other chunk below
    // are not from beginning of _id index, nor beginning of collection
    db.c.insert({_id:-10})
 
    // insert lots of documents in chunk _id>=0
    print('=== chunk insert')
    every = 10000
    var t = new Date()
    for (var i=0; i<count; ) {
        var bulk = db.c.initializeUnorderedBulkOp();
        for (var j=0; j<every && i<count; j++, i++)
            bulk.insert({_id:i})
        bulk.execute();
        tt = new Date()
        print(new Date(), 'insert', i, Math.floor(every / (tt-t) * 1000))
        t = tt
    }
    info('test.c')
 
    // move the chunk _id>0 now from shard0000 (where it starts out) to shard0001
    print('=== chunk move')
    printjson(db.adminCommand({moveChunk:'test.c', find:{_id:0}, to:'shard0001', _waitForDelete:true}))
    info('test.c')
}
 
function info(ns) {
    db.getSiblingDB("config").chunks.find({"ns" : ns}).sort({min:1}).forEach(function (chunk) { 
        var db1 = db.getSiblingDB(chunk.ns.split(".")[0])
        var key = db.getSiblingDB("config").collections.findOne({_id:chunk.ns}).key
        var size = db1.runCommand({datasize:chunk.ns, keyPattern:key, min:chunk.min, max:chunk.max, estimate:true});
        print('id', chunk._id, 'shard', chunk.shard, 'min', chunk.min._id, 'max', chunk.max._id, 'size', size.size, 'objects', size.numObjects)
    })
}

