#!/bin/bash
set -uexo pipefail
cd wiredtiger
cat bench/wtperf/runners/mongodb-oplog.wtperf | perl -npE 's/run_time=\d+/run_time=20/' > mongodb-oplog-mirror.wtperf
build/bench/wtperf/wtperf -O mongodb-oplog-mirror.wtperf
