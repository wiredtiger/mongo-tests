function find() {
    every = 1000
    var t = new Date()
    for (var i=0; ; i++) {
        db.c.find({_id:-5}).count() // search for a non-existent document
        if (i%every==0 && i>0) {
            var tt = new Date()
            print(new Date(), 'find', i, Math.floor(every / (tt-t) * 1000))
            t = tt
        }
    }
}

