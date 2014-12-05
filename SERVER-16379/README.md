Chunk Move Test
===============

Test times moving a single chunk of varying size between shards.

Output is chunk size, time to move (ms) pairs.

Running
-------

# runs shards, config srv and mongos
export MONGODB_BIN=/path/to/mongodb/bin
./run_mongo.sh

# setup shards
mongo setup_shards.js

# run a reader thread
mongo reader.js

# run the main test
mongo 16379.js


