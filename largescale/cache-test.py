#!/usr/bin/env python

import sys
import os
import time
import subprocess
import random
import datetime
import csv
from threading import Thread
from pymongo import MongoClient
from bson.binary import Binary
import data

# Test Plan
# 1. Launch MongoDB
# 2. Setup some number of collections with more data than cache
# 3. Run with an 80r/20u workload over the whole collection for a fixed time period and fixed rate of throughput
# 4. Measure the throughput over the length of the run to ensure it doesnt degrate
#
# The biggest thing we need to do is check that we have not hit the point where we are throttling eviction and that can take some tuning

# Steering

# We need to increase size by 25% to hit the intended raio. And then another 50% on top of that to ensure we have more data than cache
factor = 1.75
cache_size_gb = 10
cache_size = int(cache_size_gb * 1024 * 1024 * 1024 * factor)
random_data_size = 10000 * 100
insert_rate = 0
update_rate = 20
query_rate = 80
num_collections = 100
runtime = 3600
num_threads = 64
gross_throughput = 10000
working_set_docs = 1
collections_contents = {}
output_csv = "../results/out.csv"
oplog = 0
batch_size = 1
fail_factor = 1.2

output_filename = "results.csv"
last_ops = {"insert": 0, "update": 0, "delete": 0, "query":0, "writes":0, "write_latency":0}
dbname = "POCDB"
collname = "POCCOLL"
java_command = False

def random_string(length):
    begin = int(random.random() * random_data_size)
    end =  begin + length
    res = data.entropy[0][begin:end]
    if end > random_data_size:
        res = data.entropy[0][begin:]
        end = end - random_data_size
        res += data.entropy[0][:end]

    return res

def populate_collection(coll, rand_string_sz, docs_per):
    numInBulk = 0
    bulkSize = 1000
    bulk = coll.initialize_unordered_bulk_op()
    str1 = random_string(rand_string_sz)
    str2 = random_string(rand_string_sz)
    str3 = random_string(rand_string_sz)
    str4 = random_string(rand_string_sz)
    str5 = random_string(rand_string_sz)

    for y in range(docs_per):
        if y % bulkSize == 0 and y > 0:
           bulk.execute()
           bulk = coll.initialize_unordered_bulk_op()

        bulk.insert({ "_id" : y,
            "fld0" : random.randint(0,10000000),
            "fld1" : random.randint(0,10000000),
            "fld2" : str1,
            "fld3" : str2,
            "fld4" : str3,
            "fld5" : datetime.datetime.now(),
            "fld6" : random.randint(0,10000000),
            "fld7" : str4,
            "fld8" : str5,
            "fld9" : random.randint(0,10000000),
            "bin" : Binary("0") })

    bulk.execute()

def populate_collections(client, collections):
    global working_set_docs
    max_threads = 8
    rand_string_sz = 150
    doc = 5 * rand_string_sz + 5 * 64
    working_set_docs = cache_size / doc
    docs_per = working_set_docs / collections
    threads = []
    for x in range(collections):
        if len(threads) >= max_threads:
            t = threads.pop()
            t.join()
        ns = collname + str(x)
        coll = client[dbname][ns]
        t = Thread(target = populate_collection, args=(coll, rand_string_sz, docs_per))
        t.start()
        threads.append(t)
                
    # FsyncLock here
    client.admin.command("fsync", lock=False)

def setup_mongodb(config):
    if oplog != 0:
        client.admin.command({"replSetInitiate":{ "_id": "test", "version": 1, "members": [ { "_id": 0, "host" : "127.0.0.1:27017" } ]}})
        time.sleep(10)


def launch_poc_driver(run_collections, run_threads):
    docs_per = working_set_docs / run_collections
    FNULL = open(os.devnull, 'w')
    global java_proc
    command = ("java -jar ../POCDriver/bin/POCDriver.jar" \
               " -i " + str(insert_rate) + 
               " -u " + str(update_rate) +
               " -k " + str(query_rate) +
               " -q " + str(gross_throughput) + 
               " -z " + str(docs_per) +
               " -d " + str(runtime) +
               " -y " + str(run_collections) +
               " --collectionKeyMax " + str(docs_per) +
               " -o " + str(output_csv) +
               " -t " + str(run_threads) +
               " -b " + str(batch_size))
    print(command)
    sys.stdout.flush()
    java_proc = subprocess.Popen(command, shell=True, stdout=FNULL)

def load_from_config(filename):
    global insert_rate, update_rate, query_rate, num_collections, runtime, num_threads, gross_throughput, oplog, cache_size_gb, cache_size
    with open(filename, "r") as f:
        for line in f:
            arr = line.split('=')
            if arr[0] == "insert":
                insert_rate = int(arr[1])
            if arr[0] == "update":
                update_rate = int(arr[1])
            if arr[0] == "read":
                query_rate = int(arr[1])
            if arr[0] == "collections":
                num_collections = int(arr[1])
            if arr[0] == "runtime":
                runtime = int(arr[1])
            if arr[0] == "threads":
                num_threads = int(arr[1])
            if arr[0] == "throughput":
                gross_throughput = int(arr[1])
            if arr[0] == "oplog":
                oplog = int(arr[1])
            if arr[0] == "cache_size_gb":
                cache_size_gb = int(arr[1])
                cache_size = int(cache_size_gb * 1024 * 1024 * 1024 * factor)

def mean(arr): 
    return (sum(arr) / float(len(arr)))


def pass_fail_check():
    fail = False
    data = csv.reader(open(output_csv, 'r'), delimiter=",")
    populated = False
    w_latency = []
    w_throughput = []
    r_latency = []
    r_throughput = []
    for row in data:
        if row[0] == "system_clock":
            continue
        w_tput = int(row[6]) / float(row[10])
        r_tput = int(row[9]) / float(row[7])
        if populated:
            if int(row[6]) > mean(w_latency) * fail_factor: 
                print("Mean write latency of " + str(mean(w_latency)) + " deviated from with latency of " + row[6])
                fail = True

            if int(row[9]) > mean(r_latency) * fail_factor:
                print("Mean read latency of " + str(mean(r_latency)) + " deviated from with latency of " + row[9])
                fail = True

            if w_tput * fail_factor < mean(w_throughput):
                print("Mean write throughput of " + str(mean(w_throughput)) + " deviated from with throughput of " + str(w_tput))
                fail = True

            if r_tput * fail_factor < mean(r_throughput):
                print("Mean read throughput of " + str(mean(r_throughput)) + " deviated from with throughput of " + str(r_tput))
                fail = True

        w_latency.append(int(row[6]))
        w_throughput.append(w_tput)
        r_latency.append(int(row[9]))
        r_throughput.append(int(r_tput))

    print "Avg read throughput " + str(mean(r_throughput))
    print "Avg write throughput " + str(mean(w_throughput))
    print "Avg read latency " + str(mean(r_latency))
    print "Avg write latency " + str(mean(w_latency))

    return fail

# Main
if len(sys.argv) > 1:
    load_from_config(sys.argv[1])

client = MongoClient('mongodb://localhost:27017/')
setup_mongodb(client)
fhandle = open(output_filename, 'a')
start=time.time()

populate_collections(client, num_collections)
launch_poc_driver(num_collections, num_threads)
start = time.time()
avg_latencies = []
interval_runtime = 0
while (interval_runtime < runtime): 
    now = time.time()
    interval_runtime = now - start
    time.sleep(10)
if pass_fail_check():
    exit(123)
else:
    exit(0)
