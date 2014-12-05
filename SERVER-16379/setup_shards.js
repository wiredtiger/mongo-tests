sh.addShard('localhost:30000')
sh.addShard('localhost:31000')
 
// we'll do the chunk moving manually
printjson(['setBalancerState', sh.setBalancerState(false)])
 
