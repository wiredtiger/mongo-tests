#!/usr/bin/env python3

import sys
import os
import time
import subprocess
import random
import datetime
import csv
from pymongo import MongoClient
from bson.binary import Binary
import lorem
import multiprocessing
from multiprocessing import Pool
import concurrent.futures
import queue
import heapq

# Steering
insert_rate = 0
update_rate = 100
query_rate = 0
num_collections = 1
run_duration = 3600 * 12
num_threads = 32
limit_throughput = 10000
working_set_docs = 1000000
output_csv = "../results/out.csv"
batch_size = 1
oplog = False
populate = True

output_filename = "results.csv"
dbname = "POCDB"
collname = "POCCOLL"
collname_rand = collname + "-RANDOM"
java_command = False

verbose_level = 0

conn_str = 'mongodb://localhost:27017/'

def print_msg(module_name, level, msg):
    if level <= verbose_level:
        print("%s : %s" % (module_name, msg))


def launch_poc_driver(name, conf):
    num_collections = conf[0]
    docs_per = conf[1]
    batch_size = conf[2]
    num_threads = conf[3]
    insert_rate = conf[4]
    update_rate = conf[5]
    query_rate = conf[6]
    limit_throughput = conf[7]
    run_duration = conf[8]
    output_csv = conf[9]
    
    command = ("java -jar ../POCDriver/bin/POCDriver.jar" \
               " -i " + str(insert_rate) + 
               " -u " + str(update_rate) +
               " -k " + str(query_rate) +
               " -q " + str(limit_throughput) + 
               " -z " + str(docs_per) +
               " -d " + str(run_duration) +
               " -y " + str(num_collections) +
               " --collectionKeyMax " + str(docs_per) +
               " -o " + str(output_csv) +
               " -t " + str(num_threads) +
               " -b " + str(batch_size))

    print_msg(name, 0, "Running Java POC load generator with the following command:")
    print_msg(name, 0, command)
    
    java_proc = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    # Poll for process completion and return stdout in the meanwhile
    while java_proc.poll() is None:
        output = java_proc.stdout.readline().decode("utf-8").strip()
        while output:
            print_msg(name, 2, output)
            output = java_proc.stdout.readline().decode("utf-8").strip()
        time.sleep(1)
    
    if java_proc.poll() == 0:
        print_msg(name, 2, "Java POC load generator exited successfully")
    else:
        print_msg(name, 0, "Java POC load generator failed with return code: %d" % java_proc.poll())
        exit(123)
    sys.stdout.flush()

def launch_create_drop_loop(name, conf):
    client = conf[0]
    num_docs = conf[1]
    duration = conf[2]

    start = now = time.time()
    count = 0
    reported = False

    while now - start < duration:
        # Create a random empty collection
        ns = collname_rand + str(random.randint(0,10000000))
        client[dbname].create_collection(name=ns)
        # Insert 0 or more documents
        for y in range(num_docs):
            client[dbname][ns].insert_one(gen_random_doc(y))
        # Drop the collection
        client[dbname][ns].drop()

        # Report about progress every 10 seconds, make sure not to report more than once in a second.
        count += 1
        if int(now - start) % 10 == 0 and not reported:
            reported = True
            print_msg(name, 2, "(%d inserts): Completed iterations = %d" % (num_docs,count))
        if reported and int(now - start) % 10 > 0:
            reported = False
        now = time.time()
    print_msg(name, 1, "(%d inserts): Completed iterations = %d" % (num_docs,count))

def launch_dbstats(name, conf):
    client = conf[0]
    interval = conf[1]
    duration = conf[2]

    start = now = time.time()
    count = 0
    while now - start < duration:
        size = int(client[dbname].command("dbstats")["dataSize"]/(1024*1024))
        print_msg(name, 2, "dbstats returns dataSize: %d MB" % size)
        time.sleep(interval)
        now = time.time()
        count += 1
    print_msg(name, 1, "Ran %d times" % count)

def launch_collstats(name, conf):
    client = conf[0]
    num_colls = conf[1]
    coll_start = conf[2]
    coll_end = conf[3]
    interval = conf[4]
    duration = conf[5]

    start = now = time.time()
    count = 0
    while now - start < duration:
        size = 0
        for _ in range(num_colls):
            ns = collname + str(random.randint(coll_start, coll_end - 1))
            size += client[dbname].command("collstats", ns)["size"]
            count += 1
        print_msg(name, 2, "%d random collections return an average size of %d bytes" % (num_colls, int(size/num_colls)))
        time.sleep(interval)
        now = time.time()
    print_msg(name, 1, "Ran %d times" % count)

def launch_server_status_collector(name, conf):
    client = conf[0]
    status_q = conf[1]
    collection_time_period = conf[2]
    duration = conf[3]

    start = now = time.time()
    while now - start < duration:
        status_q.put(client.admin.command('serverStatus'))
        time.sleep(collection_time_period)
        now = time.time()
    
    # Put a "done" item on the queue to singla completion
    status_q.put({"__done_sending_req" : 1})

    # Block till all the queue has been processed
    status_q.join()

def launch_server_status_processor(name, conf):
    status_q = conf[0]
    duration = conf[1]

    # Maintain 5 best/worst overthe whole run of the stats being watched
    inserts = []
    query = []
    update = []
    reads_latency = []
    writes_latency = []
    commands_latency = []
    ckpt = []
    ckpt_prepare = []

    # Maintain a total over the whole run of the stats being watched, to calculate averages
    total_inserts = 0
    total_query = 0
    total_update = 0
    total_reads_latency = 0
    total_writes_latency = 0
    total_commands_latency = 0
    total_ckpt = 0
    total_ckpt_prepare = 0

    # Give a bit of warmup, skip first 5 data points (seconds) before watching stats
    # We end up using 2 data points to get started, so really skip 3 and call it 5
    print_msg("ServerStat", 0, "Warming up 5 seconds before status collection...")
    for _ in range(3):
        res = status_q.get()
        time.sleep(1)

    # The data is in the form:
    # { "Stat1" : [va11, val2, .. ],
    #   "Stat2" : [val1, val2, ..],
    #   "Stat3" : [val1, val2, .. ] }
    # Where it makes sense the values for a particular statistic is delta between now and the last collection point.
    # i.e., if this is a read opCounter, val2 is the amount of reads that have happened after collection of val1.
    # To be able to obtain a delta for the first value, we do not store the baseline value.
    extracted_test_data = {
        # Following stats need to be delta calculated (as a difference from the previous) 
        # opcounters
        "insert" : [],
        "query" : [],
        "update" : [],
        "command" : [],
        # command counters
        "collStats" : [],
        "create" : [],
        "dbStats" : [],
        "drop" : [],
        "listCollections" : [],
        # average opLatencies between two sample points
        "reads-latency" : [],
        "writes-latency" : [],
        "commands-latency" : [],

        # WiredTiger statistics where needed are reset on collection internally,
        # hence difference from the previous is not needed
        "checkpoint running" : [],
        "checkpoint most recent time (msecs)" : [],
        "checkpoint prepare running" : [],
        "checkpoint prepare most recent time (msecs)" : [],
        "checkpoint most recent duration for gathering all handles (usecs)" : [],
        "checkpoint most recent duration for gathering applied handles (usecs)" : [],
        "checkpoint most recent duration for gathering skipped handles (usecs)" : [],
        "checkpoint most recent handles applied" : [],
        "checkpoint most recent handles skipped" : [],
        "checkpoint most recent handles walked" : [],
        "dhandles currently active" : [],
    }

    prev = {}
    cur = {}
    count = 0
    start = time.time()
    now = time.time()
    print_msg("ServerStat", 0, "      | =====Throughput===== | =======Avg latency====== | ==== ======last ckpt duration====== =========================handles=======================")
    print_msg("ServerStat", 0, " Secs | Inserts Query Update |   reads  writes commands | ckpt last-ckpt(ms) last-prepare(ms)  active  walked(num/ms) applied(num/ms) skipped(num/ms)")
    while now - start < duration:
        res = status_q.get()
        
        # Special item to call it done!
        if "__done_sending_req" in res:
            break

        if not prev:
            # Collect baseline for stats that need a delta calculation
            prev["insert"] = res["opcounters"]["insert"]
            prev["query"] = res["opcounters"]["query"]
            prev["update"] = res["opcounters"]["update"]
            prev["command"] = res["opcounters"]["command"]
            prev["collStats"] = res["metrics"]["commands"]["collStats"]["total"]
            prev["create"] = res["metrics"]["commands"]["create"]["total"]
            prev["dbStats"] = res["metrics"]["commands"]["dbStats"]["total"]
            prev["drop"] = res["metrics"]["commands"]["drop"]["total"]
            prev["listCollections"] = res["metrics"]["commands"]["listCollections"]["total"]
            prev["reads-latency"] = res["opLatencies"]["reads"]["latency"]
            prev["reads-ops"] = res["opLatencies"]["reads"]["ops"]
            prev["writes-latency"] = res["opLatencies"]["writes"]["latency"]
            prev["writes-ops"] = res["opLatencies"]["writes"]["ops"]
            prev["commands-latency"] = res["opLatencies"]["commands"]["latency"]
            prev["commands-ops"] = res["opLatencies"]["commands"]["ops"]
            continue

        # Collect current and subtract from the previous for the delta calculation
        cur["insert"] = res["opcounters"]["insert"]
        cur["query"] = res["opcounters"]["query"]
        cur["update"] = res["opcounters"]["update"]
        cur["command"] = res["opcounters"]["command"]
        cur["collStats"] = res["metrics"]["commands"]["collStats"]["total"]
        cur["create"] = res["metrics"]["commands"]["create"]["total"]
        cur["dbStats"] = res["metrics"]["commands"]["dbStats"]["total"]
        cur["drop"] = res["metrics"]["commands"]["drop"]["total"]
        cur["listCollections"] = res["metrics"]["commands"]["listCollections"]["total"]
        cur["reads-latency"] = res["opLatencies"]["reads"]["latency"]
        cur["reads-ops"] = res["opLatencies"]["reads"]["ops"]
        cur["writes-latency"] = res["opLatencies"]["writes"]["latency"]
        cur["writes-ops"] = res["opLatencies"]["writes"]["ops"]
        cur["commands-latency"] = res["opLatencies"]["commands"]["latency"]
        cur["commands-ops"] = res["opLatencies"]["commands"]["ops"]

        # Subtract previous and current where needed and populate the data
        extracted_test_data["insert"].append(cur["insert"] - prev["insert"])
        extracted_test_data["query"].append(cur["query"] - prev["query"])
        extracted_test_data["update"].append(cur["update"] - prev["update"])
        extracted_test_data["command"].append(cur["command"] - prev["command"])
        extracted_test_data["collStats"].append(cur["collStats"] - prev["collStats"])
        extracted_test_data["create"].append(cur["create"] - prev["create"])
        extracted_test_data["dbStats"].append(cur["dbStats"] - prev["dbStats"])
        extracted_test_data["drop"].append(cur["drop"] - prev["drop"])
        extracted_test_data["listCollections"].append(cur["listCollections"] - prev["listCollections"])

        if (cur["reads-ops"] - prev["reads-ops"]) == 0:
            extracted_test_data["reads-latency"].append(0)
        else:
            extracted_test_data["reads-latency"].append(
                (cur["reads-latency"] - prev["reads-latency"]) / (cur["reads-ops"] - prev["reads-ops"]))
        if (cur["writes-ops"] - prev["writes-ops"]) == 0:
            extracted_test_data["writes-latency"].append(0)
        else:
            extracted_test_data["writes-latency"].append(
                (cur["writes-latency"] - prev["writes-latency"]) / (cur["writes-ops"] - prev["writes-ops"]))
        if (cur["commands-ops"] - prev["commands-ops"]) == 0:
            extracted_test_data["commands-latency"].append(0)
        else:
            extracted_test_data["commands-latency"].append(
                (cur["commands-latency"] - prev["commands-latency"]) / (cur["commands-ops"] - prev["commands-ops"]))

        # WiredTiger statistics don't need to be subtracted from the previous
        extracted_test_data["checkpoint running"].append(res["wiredTiger"]["transaction"]["transaction checkpoint currently running"])
        extracted_test_data["checkpoint most recent time (msecs)"].append(res["wiredTiger"]["transaction"]["transaction checkpoint most recent time (msecs)"])
        extracted_test_data["checkpoint prepare running"].append(res["wiredTiger"]["transaction"]["transaction checkpoint prepare currently running"])
        extracted_test_data["checkpoint prepare most recent time (msecs)"].append(res["wiredTiger"]["transaction"]["transaction checkpoint prepare most recent time (msecs)"])
        extracted_test_data["checkpoint most recent duration for gathering all handles (usecs)"].append(res["wiredTiger"]["transaction"]["transaction checkpoint most recent duration for gathering all handles (usecs)"])
        extracted_test_data["checkpoint most recent duration for gathering applied handles (usecs)"].append(res["wiredTiger"]["transaction"]["transaction checkpoint most recent duration for gathering applied handles (usecs)"])
        extracted_test_data["checkpoint most recent duration for gathering skipped handles (usecs)"].append(res["wiredTiger"]["transaction"]["transaction checkpoint most recent duration for gathering skipped handles (usecs)"])
        extracted_test_data["checkpoint most recent handles applied"].append(res["wiredTiger"]["transaction"]["transaction checkpoint most recent handles applied"])
        extracted_test_data["checkpoint most recent handles skipped"].append(res["wiredTiger"]["transaction"]["transaction checkpoint most recent handles skipped"])
        extracted_test_data["checkpoint most recent handles walked"].append(res["wiredTiger"]["transaction"]["transaction checkpoint most recent handles walked"])
        extracted_test_data["dhandles currently active"].append(res["wiredTiger"]["data-handle"]["connection data handles currently active"])

        # Print data every 5 data points (should equate to 5 seconds)
        if count % 5 == 0:
            print_msg("ServerStat", 0, "%5d | %7d %5d %6d | %7d %7d %8d | %4d %13d %16d %7d %7d/%7d %7d/%7d %7d/%7d" %
                (count, extracted_test_data["insert"][count], extracted_test_data["query"][count], extracted_test_data["update"][count],
                extracted_test_data["reads-latency"][count], extracted_test_data["writes-latency"][count], extracted_test_data["commands-latency"][count],
                extracted_test_data["checkpoint running"][count], extracted_test_data["checkpoint most recent time (msecs)"][count],
                extracted_test_data["checkpoint prepare most recent time (msecs)"][count], extracted_test_data["dhandles currently active"][count],
                extracted_test_data["checkpoint most recent handles walked"][count], extracted_test_data["checkpoint most recent duration for gathering all handles (usecs)"][count]/1000,
                extracted_test_data["checkpoint most recent handles applied"][count], extracted_test_data["checkpoint most recent duration for gathering applied handles (usecs)"][count]/1000,
                extracted_test_data["checkpoint most recent handles skipped"][count], extracted_test_data["checkpoint most recent duration for gathering skipped handles (usecs)"][count]/1000
            ))

        # Maintain best/worst stats
        if len(inserts) < 5:
            heapq.heappush(inserts, -1 * extracted_test_data["insert"][count])
        else:
            heapq.heappushpop(inserts, -1 * extracted_test_data["insert"][count])
        if len(query) < 5:
            heapq.heappush(query, -1 * extracted_test_data["query"][count])
        else:
            heapq.heappushpop(query, -1 * extracted_test_data["query"][count])
        if len(update) < 5:
            heapq.heappush(update, -1 * extracted_test_data["update"][count])
        else:
            heapq.heappushpop(update, -1 * extracted_test_data["update"][count])
        if len(reads_latency) < 5:
            heapq.heappush(reads_latency, extracted_test_data["reads-latency"][count])
        else:
            heapq.heappushpop(reads_latency, extracted_test_data["reads-latency"][count])
        if len(writes_latency) < 5:
            heapq.heappush(writes_latency, extracted_test_data["writes-latency"][count])
        else:
            heapq.heappushpop(writes_latency, extracted_test_data["writes-latency"][count])
        if len(commands_latency) < 5:
            heapq.heappush(commands_latency, extracted_test_data["commands-latency"][count])
        else:
            heapq.heappushpop(commands_latency, extracted_test_data["commands-latency"][count])
        if len(ckpt) < 5:
            heapq.heappush(ckpt, extracted_test_data["checkpoint most recent time (msecs)"][count])
        else:
            heapq.heappushpop(ckpt, extracted_test_data["checkpoint most recent time (msecs)"][count])
        if len(ckpt_prepare) < 5:
            heapq.heappush(ckpt_prepare, extracted_test_data["checkpoint prepare most recent time (msecs)"][count])
        else:
            heapq.heappushpop(ckpt_prepare, extracted_test_data["checkpoint prepare most recent time (msecs)"][count])

        total_inserts += extracted_test_data["insert"][count]
        total_query += extracted_test_data["query"][count]
        total_update += extracted_test_data["update"][count]
        total_reads_latency += extracted_test_data["reads-latency"][count]
        total_writes_latency += extracted_test_data["writes-latency"][count]
        total_commands_latency += extracted_test_data["commands-latency"][count]
        total_ckpt += extracted_test_data["checkpoint most recent time (msecs)"][count]
        total_ckpt_prepare += extracted_test_data["checkpoint prepare most recent time (msecs)"][count]

        count +=1
        prev = cur
        cur = {}
        now = time.time()
        status_q.task_done()
    
    print_msg("ServerStat", 0, "Total | Averages over whole run:")
    print_msg("ServerStat", 0, "%5d | %7d %5d %6d | %7d %7d %8d | ---- %13d %16d" %
        (count, total_inserts/count, total_query/count, total_update/count,
        total_reads_latency/count, total_writes_latency/count, total_commands_latency/count,
        total_ckpt/count, total_ckpt_prepare/count        
    ))

    print_msg("ServerStat", 0, "   At | Five worsts over whole:")
    for _ in range(5):
        print_msg("ServerStat", 0, "----- | %7d %5d %6d | %7d %7d %8d | ---- %13d %16d" %
            (-1 * heapq.heappop(inserts), -1 * heapq.heappop(query), -1 * heapq.heappop(update),
            heapq.heappop(reads_latency), heapq.heappop(writes_latency), heapq.heappop(commands_latency),
            heapq.heappop(ckpt), heapq.heappop(ckpt_prepare)        
    ))


# Workload and other executors mapping
exec_func_register = {
    'server_status_collector' : launch_server_status_collector,
    'server_status_processor' : launch_server_status_processor,
    'poc_driver' : launch_poc_driver,
    'create_drop_loop' : launch_create_drop_loop,
    'dbstats' : launch_dbstats,
    'collstats' : launch_collstats,
}

def thread_dist_func(conf):
    if conf[0] not in exec_func_register:
        print_msg("thread_dist_func", 0, "Error: Unregistered functionality %s." % conf[0])
        exit(123)
    else:
        print_msg(conf[0], 1, "Dispatching thread")
        exec_func_register[conf[0]](conf[0], conf[1:])
        print_msg(conf[0], 1, "Stopped after a successful run")


def random_string():
    return lorem.sentence()

def gen_random_doc(_id):
    return {
        "_id" : _id,
        "fld0" : random.randint(0,10000000),
        "fld1" : random.randint(0,10000000),
        "fld2" : random_string(),
        "fld3" : random_string(),
        "fld4" : random_string(),
        "fld5" : datetime.datetime.now(),
        "fld6" : random.randint(0,10000000),
        "fld7" : random_string(),
        "fld8" : random_string(),
        "fld9" : random.randint(0,10000000),
        "bin" : Binary("0".encode())
        }

def populate_collections_worker(pop_worker_args):
    worker_num = pop_worker_args[0]
    begin_coll = pop_worker_args[1]
    end_coll = pop_worker_args[2]
    docs_per = pop_worker_args[3]
    client = MongoClient(conn_str)

    print_msg("populate_worker", 2, "Populate worker %d starting to insert %d documents into collections %d to %d." % (worker_num, docs_per, begin_coll, end_coll))
    for x in range(begin_coll, end_coll):
        ns = collname + str(x)
        bulkSize = 1000
        bulk = client[dbname][ns].initialize_unordered_bulk_op()
        for y in range(int(docs_per)):
            if y % bulkSize == 0 and y > 0:
                bulk.execute()
                bulk = client[dbname][ns].initialize_unordered_bulk_op()
            bulk.insert(gen_random_doc(y))
        bulk.execute()
    print_msg("populate_worker", 2, "Populate worker %d finished." % worker_num)

    # Close the connection to server
    client.close()

def populate_collections(num_collections, docs_per, num_workers):
    colls_per_worker = int(num_collections / num_workers)
    pop_workers = []

    # Divide collections to populate among the workers
    for x in range(num_workers):
        begin_coll = x * colls_per_worker
        if x == num_workers - 1:
            # Populate all the remaining collections through the last worker
            end_coll = num_collections
        else:
            end_coll = (x+1) * colls_per_worker
        pop_workers.append([x+1, begin_coll, end_coll, docs_per])

    # Start workers
    print_msg("populate_collections", 0, "Starting %d workers to populate %d collections with %d documents each." % (num_workers, num_collections, docs_per))
    t1 = time.time()
    with Pool(num_workers) as p:
        p.map(populate_collections_worker, pop_workers)
    t2 = time.time()
    time_secs = t2-t1
    print_msg("populate_collections", 0, "Done. %d workers took %.2f seconds. Inserts per sec: %d." % (num_workers, time_secs, int(working_set_docs/time_secs)))

def setup_mongodb(config):
    if populate and oplog:
        print_msg("setup_mongod", 0, "MongoDB Setup: Initializing replica set.")
        client.admin.command("replSetInitiate")
        time.sleep(5)

def config_arg_to_bool(config, val):
    if val.lower() == "false":
        return False
    elif val.lower() == "true":
        return True
    else:
        print_msg("config_validation", 0, "Unsupported value for the configuration: %s=%s." % (config, val))
    exit(123)

def load_from_config(filename):
    global insert_rate, update_rate, query_rate, num_collections, run_duration, num_threads, limit_throughput, working_set_docs, oplog, populate
    with open(filename, "r") as f:
        for line in f:
            arr = line.split('=')
            # Strip newline from the value
            val = arr[1].rstrip()
            if arr[0] == "insert":
                insert_rate = int(val)
            if arr[0] == "update":
                update_rate = int(val)
            if arr[0] == "read":
                query_rate = int(val)
            if arr[0] == "collections":
                num_collections = int(val)
            if arr[0] == "runtime":
                run_duration = int(val)
            if arr[0] == "thread":
                num_threads = int(val)
            if arr[0] == "throughput":
                limit_throughput = int(val)
            if arr[0] == "working_set_docs":
                working_set_docs = int(val)
            if arr[0] == "oplog":
                oplog = config_arg_to_bool(arr[0], val)
            if arr[0] == "populate":
                populate = config_arg_to_bool(arr[0], val)


# Main
if len(sys.argv) > 1:
    load_from_config(sys.argv[1])

client = MongoClient(conn_str)
setup_mongodb(client)
fhandle = open(output_filename, 'a')
fhandle.write("time,relative_time,inserts,collections,num_writes,write_latency,average_latency\n")

docs_per = int(working_set_docs / num_collections)
# Sanity check
if docs_per * num_collections != working_set_docs:
    print_msg("main", 0, "Error: working_set_docs should be divisible by the number of collections.")
    exit(123)

# Populate by creating as many processes as the number of cpu cores available
if populate:
    populate_collections(num_collections, docs_per, multiprocessing.cpu_count())
    # FsyncLock here
    client.admin.command("fsync", lock=False)

pool_configs = []
# Configure monitor threads
server_status_q = queue.Queue()
pool_configs.append(['server_status_collector', client, server_status_q, 1, run_duration])
pool_configs.append(['server_status_processor', server_status_q, run_duration])

# Configure workloads to execute
pool_configs.append(['poc_driver', num_collections, docs_per, batch_size, num_threads,
    insert_rate, update_rate, query_rate, limit_throughput, run_duration, output_csv])
pool_configs.append(['create_drop_loop', client, 10, run_duration])
pool_configs.append(['create_drop_loop', client, 0, run_duration])
pool_configs.append(['dbstats', client, 10, run_duration])
pool_configs.append(['collstats', client, 100, 0, num_collections, 5, run_duration])

# Launch all threads
with concurrent.futures.ThreadPoolExecutor() as executor:
    futures = []
    for config in pool_configs:
        futures.append(executor.submit(thread_dist_func, conf=config))
    for future in concurrent.futures.as_completed(futures):
        if future.result() != None:
            print_msg("main", 0, "Thread failed.")

# Close the results file 
fhandle.close()

# Close the connection to server
client.close()

print_msg("main", 0, "Test Passed")