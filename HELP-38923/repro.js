/**
 * HELP-38923.
 */
(function() {
"use strict";

load("jstests/libs/parallelTester.js");

const rst = new ReplSetTest({nodes: 2, nodeOptions: {
      wiredTigerCacheSizeGB:1, setParameter: {ttlMonitorSleepSecs: 300},
      wiredTigerEngineConfigString: "timing_stress_for_test=[split_3,split_4]"}});

rst.startSet();
rst.initiateWithHighElectionTimeout();

const dbName = "test";
const collName = "38923";

const primary = rst.getPrimary();
const db = primary.getDB(dbName);

jsTestLog("Creating collection and indexes");
assert.commandWorked(db.createCollection(collName));
const coll = db.getCollection(collName);

assert.commandWorked(coll.createIndex({"lastUpdatedDateTime": 1}, {expireAfterSeconds: 300}));
//assert.commandWorked(coll.createIndex({"text3": 1}));
assert.commandWorked(coll.createIndex({"extra.text": 1}))

jsTestLog("Starting insert thread(s)");
let numThreads = 4;
let threads = [];

var insertWorkload = function(host, threadId, dbName, collName) {
    let conn = new Mongo(host);
    let db = conn.getDB(dbName);
    let coll = db.getCollection(collName);

    const batchSize = 5;

    const text = "blah and foo".repeat(1000);
    const text2 = "foo and blah".repeat(1000);

    function randomStr(length) {
        var result           = '';
        var characters       = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
        var charactersLength = characters.length;
        for ( var i = 0; i < length; i++ ) {
            result += characters.charAt(Math.floor(Math.random() * charactersLength));
        }
        return result;
    }

    let inserted = 0;
    let lastUpdatedDateTime = new Date();
    while (true) {
        const bulk = coll.initializeUnorderedBulkOp();
        for (let i = 0; i < batchSize; i++) {
            bulk.insert({
                "text": text,
                "text2": text2,
                "text3": "My ID " + threadId,
                "lastUpdatedDateTime": lastUpdatedDateTime,
                "extra.text": randomStr(100)});
        }
        assert.commandWorked(bulk.execute());
        inserted += batchSize;

        if (inserted % 25000 == 0) {
            jsTestLog("Insert thread " + threadId + " inserted " + inserted);
            sleep(300000);
            lastUpdatedDateTime = new Date();
        }
    }
};

for (let i = 0; i < numThreads; i++) {
    let t = new ScopedThread(insertWorkload, primary.host, i, dbName, collName);
    threads.push(t);
    t.start();
}

threads.forEach(function(t) {
    t.join();
});

rst.stopSet();
})();
