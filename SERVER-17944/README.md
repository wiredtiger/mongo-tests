Inserts 100K documents then removes with a delete. Inserts 100K documents then removes with a truncate

Running
-------

Run via Mongo test harness:
./buildscripts/smoke.py emptyCapped.js --storageEngine wiredTiger

Or Launch a MongoD with:
--setParameter enableTestCommands=1 --storageEngine wiredTiger
Then run:
mongo 17944.js