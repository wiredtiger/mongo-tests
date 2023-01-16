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
  {progname} <namespace> <collection> <branch> <results-file-to-upload>
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
if len(sys.argv) != 5:
    print(USAGE)
    exit()

USER = os.getenv('atlas_wt_perf_test_user')
PASSWORD = os.getenv('atlas_wt_perf_pass')
NS = sys.argv[1]
COLL = sys.argv[2]
BRANCH = sys.argv[3]
FILE_UPLOAD = sys.argv[4]

# Create connection string
client_str = "mongodb+srv://" + USER + ":" + PASSWORD + "@" + ATLAS_SERVER + \
        "/test?retryWrites=true&w=majority"

# Get the collection object
client = MongoClient(client_str)
db = client[NS]
coll = db[COLL]

upload_results_atlas(coll, BRANCH, FILE_UPLOAD)
