#!/usr/bin/env python3

"""
A script that can be used to generate workloads using POCDriver and monitor the performance of the
system through different statistics (throughput, average latency of operations, checkpoint duration,
usage of handles, ...). It prints the different statistics to the standard output and saves them to
a CSV file.
"""

import concurrent.futures
import datetime
import heapq
from posix import environ
from typing import Counter
import lorem
import multiprocessing
import os
import queue
import random
import sys
import subprocess
import time
from bson.binary import Binary
from multiprocessing import Pool
from pymongo import MongoClient
import json

PROGNAME = os.path.basename(sys.argv[0])
USAGE = """
Usage:
  {progname} <config_file>
Arguments:
  config_file: Configuration file where workload parameters are defined

Note: The easiest way to use this script is to call it from run_many_coll.sh
""".format(progname=PROGNAME)

# == Workload parameters ==
# The following parameters are used to define the workload generated by POCDriver.
# Each of these parameters can be overwritten using the provided configuration file.
batch_size = 1
collname = "POCCOLL"
conn_str = 'mongodb://localhost:27017/'
dbname = "POCDB"
enable_stats_check = False
insert_rate = 0
limit_throughput = 10000
num_collections = 1
num_threads = 32
oplog = True
output_csv = "../results/out.csv"
output_filename = "../results/results.json"
populate = True
read_rate = 0
run_duration = 3600
success = True
update_rate = 100
verbose_level = 0
working_set_docs = 1000000

collname_rand = collname + "-RANDOM"

# Helper function to print messages to the standard output.
def print_msg(module_name, level, msg):
    if level <= verbose_level:
        print("%s : %s" % (module_name, msg))

# Dump json results to the given file
def write_json_output(result):
    fhandle = open(output_filename, 'a')
    fhandle.write(json.dumps(result))
    fhandle.write("\n")
    fhandle.close()

# Execution of the POCDriver.
def launch_poc_driver(name, conf):
    num_collections = conf[0]
    docs_per = conf[1]
    batch_size = conf[2]
    num_threads = conf[3]
    insert_rate = conf[4]
    update_rate = conf[5]
    read_rate = conf[6]
    limit_throughput = conf[7]
    run_duration = conf[8]
    output_csv = conf[9]

    # Refer to https://github.com/johnlpage/POCDriver for more details.
    command = ("java -jar ../POCDriver/bin/POCDriver.jar" \
               " -i " + str(insert_rate) +
               " -u " + str(update_rate) +
               " -k " + str(read_rate) +
               " -q " + str(limit_throughput) +
               # Disabling the zipfian till we figure out another means
               # to distribute load. Using zipfian is causing POCDriver
               # to switch to older behavior - and not distribute workload
               # properly between reads/writes/inserts.
               # " -z " + str(docs_per) +
               " -d " + str(run_duration) +
               " -y " + str(num_collections) +
               " -o " + str(output_csv) +
               " -t " + str(num_threads) +
               " -b " + str(batch_size))

    print_msg(name, 0, "Running Java POC load generator with the following command:")
    print_msg(name, 0, command)

    java_proc = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
    # Poll for process completion and return stdout in the meanwhile.
    while java_proc.poll() is None:
        output = java_proc.stdout.readline().decode("utf-8").strip()
        while output:
            print_msg(name, 2, output)
            output = java_proc.stdout.readline().decode("utf-8").strip()
        time.sleep(1)

    if java_proc.poll() == 0:
        print_msg(name, 0, "Java POC load generator exited successfully")
    else:
        print_msg(name, 0, "Java POC load generator failed with return code: %d" % java_proc.poll())
        exit(123)
    sys.stdout.flush()

# Create a collection, insert documents in it and drop the collection in a loop for a given time.
def launch_create_drop_loop(name, conf):
    client = conf[0]
    num_docs = conf[1]
    duration = conf[2]

    start = now = time.time()
    count = 0
    reported = False

    while now - start < duration:
        # Create a random empty collection.
        ns = collname_rand + str(random.randint(0,10000000))
        client[dbname].create_collection(name=ns)
        # Insert 0 or more documents
        for y in range(num_docs):
            client[dbname][ns].insert_one(gen_random_doc(y))
        # Drop the collection.
        client[dbname][ns].drop()

        # Report about progress every 10 seconds, make sure not to report more than once in a
        # second.
        count += 1
        if int(now - start) % 10 == 0 and not reported:
            reported = True
            print_msg(name, 2, "(%d inserts): Completed iterations = %d" % (num_docs,count))
        if reported and int(now - start) % 10 > 0:
            reported = False
        now = time.time()
    print_msg(name, 1, "(%d inserts): Completed iterations = %d" % (num_docs,count))

# Monitoring of the database size.
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

# Monitoring of the average size of random selected collections.
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

# Gather the different statistics in a queue.
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

    # Put a "done" item on the queue to signal completion.
    status_q.put({"__done_sending_req" : 1})

# Process the different statistics in the queue
def launch_server_status_processor(name, conf):
    status_q = conf[0]
    duration = conf[1]

    # Throughput stats
    stalled_counters = {"insert": 0, "query": 0, "update": 0}

    # Maintain 5 best/worst over the whole run of the stats being watched.
    ckpt = []
    ckpt_prepare = []
    commands_latency = []
    inserts = []
    query = []
    reads_latency = []
    update = []
    writes_latency = []

    # Maintain a total over the whole run of the stats being watched to calculate averages.
    total_ckpt = 0
    total_ckpt_prepare = 0
    total_commands_latency = 0
    total_inserts = 0
    total_query = 0
    total_reads_latency = 0
    total_update = 0
    total_writes_latency = 0

    # Save results for dumping as a json
    result = {}

    # Give a bit of warmup, skip first 3 data points (seconds) before watching stats.
    print_msg("ServerStat", 0, "Warming up 3 seconds before status collection...")
    for _ in range(3):
        res = status_q.get()
        time.sleep(1)

    # The data is in the form:
    # { "Stat1" : [val1, val2, .. ],
    #   "Stat2" : [val1, val2, ..],
    #   "Stat3" : [val1, val2, .. ] }
    # Where it makes sense the values for a particular statistic is delta between now and the last collection point.
    # i.e., if this is a read opCounter, val2 is the amount of reads that have happened after collection of val1.
    # To be able to obtain a delta for the first value, we do not store the baseline value.
    extracted_test_data = {
        # Following stats need to be delta calculated (as a difference from the previous).
        # opcounters.
        "command" : [],
        "insert" : [],
        "query" : [],
        "update" : [],
        # command counters.
        "collStats" : [],
        "create" : [],
        "dbStats" : [],
        "drop" : [],
        "listCollections" : [],

        # average opLatencies between two sample points.
        "commands-latency" : [],
        "reads-latency" : [],
        "writes-latency" : [],

        # WiredTiger statistics where needed are reset on collection internally,
        # hence difference from the previous is not needed.
        "checkpoint most recent time (msecs)" : [],
        "checkpoint running" : [],
        "dhandles currently active" : [],
    }

    count = 0
    cur = {}
    now = time.time()
    prev = {}
    start = time.time()

    print_msg("ServerStat", 0, "      | =====Throughput===== | =======Avg latency====== | ==== ======last ckpt duration======")
    print_msg("ServerStat", 0, " Secs | Inserts Query Update |   reads  writes commands | ckpt last-ckpt(ms) ")

    while now - start < duration:
        res = status_q.get()

        # Special item to call it done!
        if "__done_sending_req" in res:
            break

        if not prev:
            # Collect baseline for stats that need a delta calculation.
            prev["command"] = res["opcounters"]["command"]
            prev["insert"] = res["opcounters"]["insert"]
            prev["query"] = res["opcounters"]["query"]
            prev["update"] = res["opcounters"]["update"]
            prev["collStats"] = res["metrics"]["commands"]["collStats"]["total"]
            prev["create"] = res["metrics"]["commands"]["create"]["total"]
            prev["dbStats"] = res["metrics"]["commands"]["dbStats"]["total"]
            prev["drop"] = res["metrics"]["commands"]["drop"]["total"]
            prev["listCollections"] = res["metrics"]["commands"]["listCollections"]["total"]
            prev["commands-latency"] = res["opLatencies"]["commands"]["latency"]
            prev["reads-latency"] = res["opLatencies"]["reads"]["latency"]
            prev["writes-latency"] = res["opLatencies"]["writes"]["latency"]
            prev["commands-ops"] = res["opLatencies"]["commands"]["ops"]
            prev["reads-ops"] = res["opLatencies"]["reads"]["ops"]
            prev["writes-ops"] = res["opLatencies"]["writes"]["ops"]
            continue

        # Collect current and subtract from the previous for the delta calculation.
        cur["command"] = res["opcounters"]["command"]
        cur["insert"] = res["opcounters"]["insert"]
        cur["query"] = res["opcounters"]["query"]
        cur["update"] = res["opcounters"]["update"]
        cur["collStats"] = res["metrics"]["commands"]["collStats"]["total"]
        cur["create"] = res["metrics"]["commands"]["create"]["total"]
        cur["dbStats"] = res["metrics"]["commands"]["dbStats"]["total"]
        cur["drop"] = res["metrics"]["commands"]["drop"]["total"]
        cur["listCollections"] = res["metrics"]["commands"]["listCollections"]["total"]
        cur["commands-latency"] = res["opLatencies"]["commands"]["latency"]
        cur["reads-latency"] = res["opLatencies"]["reads"]["latency"]
        cur["writes-latency"] = res["opLatencies"]["writes"]["latency"]
        cur["commands-ops"] = res["opLatencies"]["commands"]["ops"]
        cur["reads-ops"] = res["opLatencies"]["reads"]["ops"]
        cur["writes-ops"] = res["opLatencies"]["writes"]["ops"]

        # Subtract previous and current where needed and populate the data.
        extracted_test_data["command"].append(cur["command"] - prev["command"])
        extracted_test_data["insert"].append(cur["insert"] - prev["insert"])
        extracted_test_data["query"].append(cur["query"] - prev["query"])
        extracted_test_data["update"].append(cur["update"] - prev["update"])
        extracted_test_data["collStats"].append(cur["collStats"] - prev["collStats"])
        extracted_test_data["create"].append(cur["create"] - prev["create"])
        extracted_test_data["dbStats"].append(cur["dbStats"] - prev["dbStats"])
        extracted_test_data["drop"].append(cur["drop"] - prev["drop"])
        extracted_test_data["listCollections"].append(cur["listCollections"] - prev["listCollections"])

        # Compute the average of opLatencies between the current and previous sample points.
        if (cur["commands-ops"] - prev["commands-ops"]) == 0:
            extracted_test_data["commands-latency"].append(0)
        else:
            extracted_test_data["commands-latency"].append(
                (cur["commands-latency"] - prev["commands-latency"]) / (cur["commands-ops"] - prev["commands-ops"]))
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

        # WiredTiger statistics don't need to be subtracted from the previous.
        extracted_test_data["checkpoint most recent time (msecs)"].append(res["wiredTiger"]["transaction"]["transaction checkpoint most recent time (msecs)"])
        extracted_test_data["checkpoint running"].append(res["wiredTiger"]["transaction"]["transaction checkpoint currently running"])
        extracted_test_data["dhandles currently active"].append(res["wiredTiger"]["data-handle"]["connection data handles currently active"])

        # Print data every 5 data points (should equate to 5 seconds).
        if count % 5 == 0:
            print_msg("ServerStat", 0, "%5d | %7d %5d %6d | %7d %7d %8d | %4d %13d" %
                (count, extracted_test_data["insert"][count], extracted_test_data["query"][count], extracted_test_data["update"][count],
                extracted_test_data["reads-latency"][count], extracted_test_data["writes-latency"][count], extracted_test_data["commands-latency"][count],
                extracted_test_data["checkpoint running"][count], extracted_test_data["checkpoint most recent time (msecs)"][count]
            ))

        # Check for stalls
        for stat in stalled_counters:
            if(extracted_test_data[stat][count] == 0):
                stalled_counters[stat] = stalled_counters[stat] + 1

        # Maintain best/worst stats.
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

        # Update the total stats.
        total_inserts += extracted_test_data["insert"][count]
        total_query += extracted_test_data["query"][count]
        total_update += extracted_test_data["update"][count]
        total_reads_latency += extracted_test_data["reads-latency"][count]
        total_writes_latency += extracted_test_data["writes-latency"][count]
        total_commands_latency += extracted_test_data["commands-latency"][count]
        total_ckpt += extracted_test_data["checkpoint most recent time (msecs)"][count]

        count +=1
        prev = cur
        cur = {}
        now = time.time()
        status_q.task_done()

    result["Run Duration"] = count
    result["Number of collections"] = num_collections
    result["Working set document count"] = working_set_docs
    result["Average inserts"] = total_inserts/count
    result["Average queries"] = total_query/count
    result["Average updates"] = total_update/count
    result["Average read latency"] = total_reads_latency/count
    result["Average write latency"] = total_writes_latency/count
    result["Average command latency"] = total_commands_latency/count
    result["Average checkpoint duration"] = total_ckpt/count
    print_msg("ServerStat", 0, "Total | Averages over whole run")
    print_msg("ServerStat", 0, "%5d | %7d %5d %6d | %7d %7d %8d | ---- %13d" %
        (count, result["Average inserts"], result["Average queries"], result["Average updates"], result["Average read latency"], result["Average write latency"],
        result["Average command latency"], result["Average checkpoint duration"]
    ))

    worst_ckpt_duration_value = 0
    worst_ckpt_preparation_value = 0
    worst_commands_latency_value = 0
    worst_reads_latency_value = 0
    worst_writes_latency_value = 0
    print_msg("ServerStat", 0, "   At | Five worsts over whole run")
    num_samples = min(5, len(inserts))
    for index in range(num_samples):
        if index < num_samples - 1:
            # index = 3 is 5 - 3 = 2 , 2nd worst latency
            slow_ins_rate = result["Worst per-sec insert throughput " + str(num_samples - index)] = -1 * heapq.heappop(inserts)
            slow_query_rate = result["Worst per-sec query throughput " + str(num_samples - index)] = -1 * heapq.heappop(query)
            slow_update_rate = result["Worst per-sec update throughput " + str(num_samples - index)] = -1 * heapq.heappop(update)
            slow_reads_latency = result["Worst per-sec reads latency " + str(num_samples - index)] = heapq.heappop(reads_latency)
            slow_writes_latency = result["Worst per-sec writes latency " + str(num_samples - index)] = heapq.heappop(writes_latency)
            slow_commands_latency = result["Worst per-sec commands latency " + str(num_samples - index)] = heapq.heappop(commands_latency)
            slow_ckpt_duration = result["Worst checkpoint duration " + str(num_samples - index)] = heapq.heappop(ckpt)
            print_msg("ServerStat", 0, "----- | %7d %5d %6d | %7d %7d %8d | ---- %13d" %
                (slow_ins_rate, slow_query_rate, slow_update_rate,
                 slow_reads_latency, slow_writes_latency, slow_commands_latency,
                 slow_ckpt_duration))
        else:
            # Save the values for future check
            worst_ins_rate = result["Worst per-sec insert throughput"] = -1 * heapq.heappop(inserts)
            worst_query_rate = result["Worst per-sec query throughput"] = -1 * heapq.heappop(query)
            worst_update_rate = result["Worst per-sec update throughput"] = -1 * heapq.heappop(update)
            worst_ckpt_duration_value = result["Worst checkpoint duration"] = heapq.heappop(ckpt)
            worst_commands_latency_value = result["Worst per-sec commands latency"] = heapq.heappop(commands_latency)
            worst_reads_latency_value = result["Worst per-sec reads latency"] = heapq.heappop(reads_latency)
            worst_writes_latency_value = result["Worst per-sec writes latency"] = heapq.heappop(writes_latency)
            print_msg("ServerStat", 0, "----- | %7d %5d %6d | %7d %7d %8d | ---- %13d" %
                (worst_ins_rate, worst_query_rate, worst_update_rate,
                worst_reads_latency_value, worst_writes_latency_value, worst_commands_latency_value,
                worst_ckpt_duration_value))

    print_msg("Stalls over whole run", 0, "")
    for stat in stalled_counters:
        print_msg("Number of " + stat + " stalled", 0, "%d" % stalled_counters[stat])
        result["Times " + stat + " stalled"] = stalled_counters[stat]

    global success
    if enable_stats_check:

        if stalled_counters["insert"] > max_stalled_inserts:
            print("Too many stalled inserts: %d. Max allowed: %d" % (stalled_counters["insert"], max_stalled_inserts))
            success = False
        if stalled_counters["query"] > max_stalled_queries:
            print("Too many stalled queries: %d. Max allowed: %d" % (stalled_counters["query"], max_stalled_queries))
            success = False
        if stalled_counters["update"] > max_stalled_updates:
            print("Too many stalled updates: %d. Max allowed: %d" % (stalled_counters["update"], max_stalled_updates))
            success = False
        
        if result["Average inserts"] < min_avg_inserts:
            print("Average number of insert operations is too low: %d. Min allowed: %d" % (result["Average inserts"], min_avg_inserts))
            success = False
        if result["Average queries"] < min_avg_queries:
            print("Average number of query operations is too low: %d. Min allowed: %d" % (result["Average queries"], min_avg_queries))
            success = False
        if result["Average updates"] < min_avg_updates:
            print("Average number of update operations is too low: %d. Min allowed: %d" % (result["Average updates"], min_avg_updates))
            success = False

        if result["Average read latency"] > max_avg_reads_latency:
            print("Average reads latency is too high: %d. Max allowed: %d" % (result["Average read latency"], max_avg_reads_latency))
            success = False
        if result["Average write latency"] > max_avg_writes_latency:
            print("Average writes latency is too high: %d. Max allowed: %d" % (result["Average write latency"], max_avg_writes_latency))
            success = False
        if result["Average command latency"] > max_avg_commands_latency:
            print("Average commands latency is too high: %d. Max allowed: %d" % (result["Average command latency"], max_avg_commands_latency))
            success = False

        if result["Average checkpoint duration"] > max_avg_ckpt_duration:
            print("Average checkpoint duration is too high: %d ms. Max allowed: %d ms" % (result["Average checkpoint duration"], max_avg_ckpt_duration))
            success = False

        if worst_ckpt_duration_value > worst_ckpt_duration:
            print("Checkpoint duration has exceeded the limit: %d ms. Max allowed: %d ms" % (worst_ckpt_duration_value, worst_ckpt_duration))
            success = False
        if worst_commands_latency_value > worst_commands_latency:
            print("Commands latency has exceeded the limit: %d. Max allowed: %d" % (worst_commands_latency_value, worst_commands_latency))
            success = False
        if worst_reads_latency_value > worst_reads_latency:
            print("Reads latency has exceeded the limit: %d. Max allowed: %d" % (worst_reads_latency_value, worst_reads_latency))
            success = False
        if worst_writes_latency_value > worst_writes_latency:
            print("Writes latency has exceeded the limit: %d. Max allowed: %d" % (worst_writes_latency_value, worst_writes_latency))
            success = False

    # Let's write the output to the output file
    write_json_output(result)

# Workload and other executors mapping.
exec_func_register = {
    'server_status_collector' : launch_server_status_collector,
    'server_status_processor' : launch_server_status_processor,
    'poc_driver' : launch_poc_driver,
    'create_drop_loop' : launch_create_drop_loop,
    'dbstats' : launch_dbstats,
    'collstats' : launch_collstats,
}

# Create a thread given a configuration.
def thread_dist_func(conf):
    if conf[0] not in exec_func_register:
        print_msg("thread_dist_func", 0, "Error: Unregistered functionality %s." % conf[0])
        exit(123)
    else:
        print_msg(conf[0], 1, "Dispatching thread")
        exec_func_register[conf[0]](conf[0], conf[1:])
        print_msg(conf[0], 1, "Stopped after a successful run")

# Generate a random string.
def random_string():
    return lorem.sentence()

# Generate a doc with fields associated to random values.
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

# Populate a collection.
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

    # Close the connection to server.
    client.close()

# Populate the database.
def populate_collections(num_collections, docs_per, num_workers):
    colls_per_worker = int(num_collections / num_workers)
    pop_workers = []

    # Divide collections to populate among the workers.
    for x in range(num_workers):
        begin_coll = x * colls_per_worker
        if x == num_workers - 1:
            # Populate all the remaining collections through the last worker.
            end_coll = num_collections
        else:
            end_coll = (x+1) * colls_per_worker
        pop_workers.append([x+1, begin_coll, end_coll, docs_per])

    # Start workers.
    print_msg("populate_collections", 0, "Starting %d workers to populate %d collections with %d documents each." % (num_workers, num_collections, docs_per))
    t1 = time.time()
    with Pool(num_workers) as p:
        p.map(populate_collections_worker, pop_workers)
    t2 = time.time()
    time_secs = t2-t1
    print_msg("populate_collections", 0, "Done. %d workers took %.2f seconds. Inserts per sec: %d." % (num_workers, time_secs, int(working_set_docs/time_secs)))

# MongoDB setup by initiating a replica set.
def setup_mongodb():
    print_msg("setup_mongod", 0, "MongoDB Setup: Initializing replica set.")
    client.admin.command("replSetInitiate")
    print_msg("setup_mongodb", 0, "Sleeping 5 seconds...")
    time.sleep(5)

def config_arg_to_bool(config, val):
    if val.lower() == "false":
        return False
    elif val.lower() == "true":
        return True
    else:
        print_msg("config_validation", 0, "Unsupported value for the configuration: %s=%s." % (config, val))
    exit(123)

# Parse a configuration file.
def load_from_config(filename):
    # Workload parameters.
    global batch_size, collname, conn_str, dbname, enable_stats_check, insert_rate, \
    limit_throughput, num_collections, num_threads, oplog, output_csv, output_filename, populate, \
    read_rate, run_duration, update_rate, verbose_level, working_set_docs
    # Performance thresholds.
    global max_avg_commands_latency, max_avg_ckpt_duration, max_avg_ckpt_preparation, \
    max_avg_reads_latency, max_avg_writes_latency, max_stalled_inserts, max_stalled_queries, \
    max_stalled_updates, min_avg_inserts, min_avg_queries, min_avg_updates, num_collections, \
    worst_reads_latency, worst_writes_latency, worst_commands_latency, worst_ckpt_duration, \
    worst_ckpt_preparation
    with open(filename, "r") as f:
        for line in f:
            if line.isspace() or line.startswith('#'):
                continue
            arr = line.split('=')
            # Strip newline from the value.
            val = arr[1].rstrip()
            if arr[0] == "batch_size":
                batch_size = int(val)
            if arr[0] == "collname":
                collname = val
            if arr[0] == "conn_str":
                conn_str = val
            if arr[0] == "dbname":
                dbname = val
            if arr[0] == "enable_stats_check":
                enable_stats_check = config_arg_to_bool(arr[0], val)
            if arr[0] == "insert_rate":
                insert_rate = int(val)
            if arr[0] == "limit_throughput":
                limit_throughput = int(val)
            if arr[0] == "max_avg_commands_latency":
                max_avg_commands_latency = int(val)
            if arr[0] == "max_avg_ckpt_duration":
                max_avg_ckpt_duration = int(val)
            if arr[0] == "max_avg_ckpt_preparation":
                max_avg_ckpt_preparation = int(val)
            if arr[0] == "max_avg_reads_latency":
                max_avg_reads_latency = int(val)
            if arr[0] == "max_avg_writes_latency":
                max_avg_writes_latency = int(val)
            if arr[0] == "max_stalled_inserts":
                max_stalled_inserts = int(val)
            if arr[0] == "max_stalled_queries":
                max_stalled_queries = int(val)
            if arr[0] == "max_stalled_updates":
                max_stalled_updates = int(val)
            if arr[0] == "min_avg_inserts":
                min_avg_inserts = int(val)
            if arr[0] == "min_avg_queries":
                min_avg_queries = int(val)
            if arr[0] == "min_avg_updates":
                min_avg_updates = int(val)
            if arr[0] == "num_collections":
                num_collections = int(val)
            if arr[0] == "num_thread":
                num_threads = int(val)
            if arr[0] == "oplog":
                oplog = config_arg_to_bool(arr[0], val)
            if arr[0] == "output_csv":
                output_csv = val
            if arr[0] == "output_filename":
                output_filename = val
            if arr[0] == "populate":
                populate = config_arg_to_bool(arr[0], val)
            if arr[0] == "read_rate":
                read_rate = int(val)
            if arr[0] == "run_duration":
                run_duration = int(val)
            if arr[0] == "update_rate":
                update_rate = int(val)
            if arr[0] == "verbose_level":
                verbose_level = int(val)
            if arr[0] == "working_set_docs":
                working_set_docs = int(val)
            if arr[0] == "worst_reads_latency":
                worst_reads_latency = int(val)
            if arr[0] == "worst_writes_latency":
                worst_writes_latency = int(val)
            if arr[0] == "worst_commands_latency":
                worst_commands_latency = int(val)
            if arr[0] == "worst_ckpt_duration":
                worst_ckpt_duration = int(val)
            if arr[0] == "worst_ckpt_preparation":
                worst_ckpt_preparation = int(val)

# Allow overriding some of the config from environmental variables
def override_from_environ():
    # Workload parameters.
    global num_collections, run_duration, working_set_docs

    # Override if any configuration parameter provided as an environmental variable.
    if "many_coll_num_collections" in os.environ:
        num_collections = int(os.environ["many_coll_num_collections"])
    if "many_coll_run_duration" in os.environ:
        run_duration = int(os.environ["many_coll_run_duration"])
    if "many_coll_working_set_docs" in os.environ:
        working_set_docs = int(os.environ["many_coll_working_set_docs"])

# Main
if len(sys.argv) > 1:
    if(sys.argv[1] == "-h"):
        print(USAGE)
        exit()
    else:
        load_from_config(sys.argv[1])
else:
    print_msg("main", 0, "No configuration provided, using default workload values")

# Allow some configuration to be overridden with environment variables.
override_from_environ()

# Start MongDB.
client = MongoClient(conn_str)
# Set up MongoDB.
if oplog:
    setup_mongodb()

docs_per = int(working_set_docs / num_collections)
# Sanity check.
if docs_per * num_collections != working_set_docs:
    print_msg("main", 0, "Error: working_set_docs should be divisible by the number of collections.")
    exit(123)

# Populate by creating as many processes as the number of cpu cores available.
if populate:
    populate_collections(num_collections, docs_per, multiprocessing.cpu_count())
    # FsyncLock here.
    client.admin.command("fsync", lock=False)

pool_configs = []
# Configure monitor threads.
server_status_q = queue.Queue()

collection_time_period_s = 1
pool_configs.append(['server_status_collector', client, server_status_q, collection_time_period_s, run_duration])

pool_configs.append(['server_status_processor', server_status_q, run_duration])

# Configure workloads to execute.
pool_configs.append(['poc_driver', num_collections, docs_per, batch_size, num_threads,
    insert_rate, update_rate, read_rate, limit_throughput, run_duration, output_csv])

num_docs = 10
pool_configs.append(['create_drop_loop', client, num_docs, run_duration])

num_docs = 0
pool_configs.append(['create_drop_loop', client, num_docs, run_duration])

interval_s = 10
pool_configs.append(['dbstats', client, interval_s, run_duration])

num_colls = 100
coll_start = 0
interval_s = 5
pool_configs.append(['collstats', client, num_colls, coll_start, num_collections, interval_s, run_duration])

# Launch all threads.
with concurrent.futures.ThreadPoolExecutor() as executor:
    futures = []
    for config in pool_configs:
        futures.append(executor.submit(thread_dist_func, conf=config))
    for future in concurrent.futures.as_completed(futures):
        if future.result() != None:
            print_msg("main", 0, "Thread failed.")
            success = False
        else:
            print_msg("main", 2, "One thread finished working !")

# Close the connection to server.
print_msg("main", 0, "Closing client's connection...")
client.close()

if success:
    print_msg("main", 0, "Test Passed")
    sys.exit(0)

else:
    print_msg("main", 0, "Test failed")
    sys.exit(1)
