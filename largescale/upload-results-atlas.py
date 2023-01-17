#!/usr/bin/env python3

"""
A script to upload the results from a perf test to an Atlas instance
"""

import os
import sys
import pymongo
from pymongo import MongoClient
import json
import datetime

PROGNAME = os.path.basename(sys.argv[0])
USAGE = """
Usage:
  {progname} [<user-name> <password>] <namespace> <collection> <branch> <results-file-to-upload>
""".format(progname=PROGNAME)

ATLAS_SERVER = "perfvisual.j1trn.mongodb.net"

# Upload the results to an Atlas instance
def upload_results_atlas(coll, branch, filename):
    with open(filename, "r") as f:
        for line in f:
            if line.isspace() or line.startswith('#'):
                continue
            line_dict = json.loads(line)
            upload_doc = {}
            upload_doc["Timestamp"] = datetime.datetime.now()
            upload_doc["Branch"] = branch
            upload_doc.update(line_dict)
            coll.insert_one(upload_doc)

# Main
arg_count = len(sys.argv)
if arg_count != 5 and arg_count != 7:
    print(USAGE)
    exit()

argv_it = iter(sys.argv)
# Ignore the first argv.
next(argv_it)
if arg_count == 5:
    USER = os.getenv('atlas_wt_perf_test_user')
    PASSWORD = os.getenv('atlas_wt_perf_pass')
else:
    USER = next(argv_it)
    PASSWORD = next(argv_it)
NS = next(argv_it)
COLL = next(argv_it)
BRANCH = next(argv_it)
FILE_UPLOAD = next(argv_it)

# Create connection string
client_str = "mongodb+srv://" + USER + ":" + PASSWORD + "@" + ATLAS_SERVER + \
        "/test?retryWrites=true&w=majority"

# Get the collection object
client = MongoClient(client_str)
db = client[NS]
coll = db[COLL]

upload_results_atlas(coll, BRANCH, FILE_UPLOAD)
