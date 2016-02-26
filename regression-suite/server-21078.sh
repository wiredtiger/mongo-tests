runTest() {
    ./mongo --nodb <<EOF
(function() {
    "use strict";
    var ex;
    var port = 20000;
    var pid = _startMongoProgram.apply(
        null,
        ['mongod', '--storageEngine=wiredTiger','--nojournal', '--port', port]);
    var mongo;
    assert.soon(function () {
        var ex;
        try {
            mongo = new Mongo("127.0.0.1:" + port)
            return true;
        } catch (ex) {
            if (!checkProgram(pid)) { throw ex;}
        }
        return false;
    });
    var psh = startParallelShell("while(true) { db.runCommand({getlasterror: 1, fsync: true}) }",
                                 port);
    sleep(1000);
    try {
        mongo.adminCommand("shutdown");
    } catch (ex) { /* expected */}
    assert.eq(0, waitProgram(pid), "waiting for " + pid);
})();
EOF
}

i=1
#-> start mongo
while runTest && [ $i -lt 10 ]; do (( ++i )); done
#-> stop mongod

if [ $i -ne 10 ]; then
	echo "test failed, did not successfully complete 10 runs"
	exit 1
fi
