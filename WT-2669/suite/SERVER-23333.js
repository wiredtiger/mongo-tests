// Tests the high-water memory fragmentation level incurred by the allocator
// while running on WiredTiger. The maximum allowed fragmentation should be
// limited to a percentage of the WiredTiger cache size.

(function() {
    "use strict";

    var conn = MongoRunner.runMongod({
        syncdelay: "0",
        storageEngine: "wiredTiger",
        wiredTigerCacheSizeGB: "1.0",
        nojournal: ""
    });
    var allocatorFragmentationDB = conn.getDB("allocatorFragmentation");

    // For access to ScopedThread and CountDownLatch.
    load("jstests/libs/parallelTester.js");

    // The acceptable maximum fragmentation is 10% of the WiredTiger cache size.
    var wiredTigerCacheSizeBytes =
        allocatorFragmentationDB.serverStatus().wiredTiger.cache["maximum bytes configured"];
    var fragmentationLimitPercentage = 0.1;

    // Check the fragmentation percentage before running the workload.
    var startFragmentation =
        allocatorFragmentationDB.serverStatus({tcmalloc: 1}).tcmalloc.tcmalloc.total_free_bytes;
    print("Initial fragmentation is " + startFragmentation + " bytes (" +
          (startFragmentation / wiredTigerCacheSizeBytes) * 100 + "% of cache)");

    // Unfortunately, FTDC data is not accessible at all through the shell. This thread polls
    // serverStatus in a manner similar to FTDC, keeping track of the highest level of
    // fragmentation.
    var serverStatusMonitor =
        function(countDownLatch, host) {
            "use strict";

            // Get a handle to a database -- doesn't matter which, as we just run serverStatus.
            var mongo = new Mongo(host);
            var testDB = mongo.getDB("test");

            var max = {
                totalFreeBytes: 0
            };

            // Loops indefinitely until another thread steps this latch down to zero.
            while (countDownLatch.getCount() > 0) {
                var s = testDB.runCommand({
                    serverStatus: 1,
                    tcmalloc: 1,
                    asserts: 0,
                    backgroundFlushing: 0,
                    dur: 0,
                    extra_info: 0,
                    globalLock: 0,
                    locks: 0,
                    mem: 0,
                    metrics: 0,
                    network: 0,
                    opcounters: 0,
                    opcountersRepl: 0,
                    rangeDeleter: 0,
                    repl: 0,
                    security: 0,
                    storageEngine: 0,
                    wiredTiger: 0,
                    writeBacksQueued: 0,
                    connections: 0
                });

                var fragmentation = s.tcmalloc.tcmalloc.total_free_bytes;
                if (fragmentation > max["totalFreeBytes"]) {
                    max["totalFreeBytes"] = fragmentation;
                    max["localTime"] = s.localTime;
                }
            }

            return max;
        }

    // Launch the serverStatus monitor.
    var latch = new CountDownLatch(1);
    var serverStatusMonitorThread = new ScopedThread(serverStatusMonitor, latch, conn.host);
    serverStatusMonitorThread.start();

    // Using multiple threads, creates a collection whose size matches the configured WiredTiger
    // cache size.
    var createLargeCollectionInParallel =
        function(host, collName, numThreads) {
            // Helper function to insert documents (and create indexes).
            var insertDocuments =
                function(host, collName) {
                    var mongo = new Mongo(host);
                    var allocatorFragmentationDB = mongo.getDB("allocatorFragmentation");
                    var coll = mongo.getDB("allocatorFragmentation").getCollection(collName);
                    coll.createIndex({a: 1});
                    coll.createIndex({b: 1});
                    coll.createIndex({c: 1});

                    var targetSize = allocatorFragmentationDB.serverStatus()
                                         .wiredTiger.cache["maximum bytes configured"];
                    var doc = {
                        a: 1,
                        b: 1,
                        c: 1
                    };
                    while (coll.stats().size < targetSize) {
                        // Insert 1000 documents at a time.
                        var bulk = coll.initializeUnorderedBulkOp();
                        for (var i = 0; i < 1000; i++) {
                            bulk.insert(doc);
                        }
                        assert.writeOK(bulk.execute());
                    }
                }

            var threads = [];
            for (var i = 0; i < numThreads; i++) {
                var thread = new ScopedThread(insertDocuments, host, collName);
                threads.push(thread);
                thread.start();
            }

            threads.forEach(function(thread) {
                thread.join();
            });
        }

    // Create two large collections with 16 threads each.
    print("Creating first collection");
    createLargeCollectionInParallel(conn.host, "first", 16);
    print("Creating second collection");
    createLargeCollectionInParallel(conn.host, "second", 16);

    // Scan the first collection to load it back into cache.
    print("Loading first collection back into cache");
    var firstColl = allocatorFragmentationDB.first;
    firstColl.find({}).itcount();

    // End the monitoring.
    latch.countDown();
    serverStatusMonitorThread.join();

    // What was the highest level of fragmentation seen during the test?
    var result = serverStatusMonitorThread.returnData();
    var fragmentationBytes = result["totalFreeBytes"];
    print("Max fragmentation during test:");
    printjson(result);

    // Clean up now, in case the assertion fails.
    allocatorFragmentationDB.dropDatabase();

    print("WiredTiger cache size:          " + wiredTigerCacheSizeBytes + " bytes");
    print("Highest observed fragmentation: " + fragmentationBytes + " bytes");
    assert(fragmentationBytes < (wiredTigerCacheSizeBytes * fragmentationLimitPercentage),
           "Fragmentation is " + ((fragmentationBytes / wiredTigerCacheSizeBytes) * 100) +
               "% of cache size, which exceeds threshold of " +
               (fragmentationLimitPercentage * 100) + "%");

}());

