var t = db.slow_truncate;
 
function insert() {
    for (var i=0; i<100*1000; i++) t.insert({_id: i});
}
 
print("insert: " + Date.timeFunc(insert));
print("remove: " + Date.timeFunc(function() {t.remove({})}));
 
t.drop(); // start next phase clean
 
print("insert: " + Date.timeFunc(insert));
print("trunc: " + Date.timeFunc(function() {t.runCommand('emptycapped')})); // does a truncate