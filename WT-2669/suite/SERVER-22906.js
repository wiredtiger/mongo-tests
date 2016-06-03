function update(count) {
    while(count--) {
        var l = Math.random()*200
        x = ''
        while (x.length < l)
            x += 'xxxxxxxxxxxx'
        var id = Math.floor(Math.random()*count)
        db.c.update({_id:id}, {$push:{x:x}}, {upsert:true})
    }
}
 
update(100000);
