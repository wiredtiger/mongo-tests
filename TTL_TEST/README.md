## Attempted reproducer for WT_NOTFOUND bug
## Requirements:

1. Compile mongodbcxx following the instructions here:
http://mongocxx.org/mongocxx-v3/installation/
2. Have a version of mongodb available.

## Compile and run instructions:
To compile run the following (change the location of your mongo-cxx-driver as required):

    export LD_LIBRARY_PATH=/opt/mongo-cxx-driver/lib/
    export PKG_CONFIG_PATH=/opt/mongo-cxx-driver/lib/ pkgconfig/
    c++ --std=c++11 repro.cpp $(pkg-config --cflags --libs libmongocxx) -lpthread -o repro

To run (needs default mongod running):
1. In your mongod repro run the ./runner.sh script, this will start your mongod and point it at the database directory passed specified on the command line.

       ./runner.sh $DBPATH
2. In a separate shell run ./repro

