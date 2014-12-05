sh.addShard('localhost:30000')
sh.addShard('localhost:31000')
 
// turn on sharding for collection test.c
printjson(['enableSharding', sh.enableSharding('test')])
printjson(['shardCollection', sh.shardCollection('test.c', {_id: 1})])
 
// we'll do the chunk moving manually
printjson(['setBalancerState', sh.setBalancerState(false)])
 
// manually create two chunks: _id<0 and _id>=0
printjson(['split', db.adminCommand({split: 'test.c', middle: {_id:0}})])

