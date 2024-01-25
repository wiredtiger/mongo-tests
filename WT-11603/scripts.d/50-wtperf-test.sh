#!/bin/bash
set -uexo pipefail
cd "wiredtiger/build/bench/wtperf"
./wtperf -O ../../../../pack.wtperf
egrep '[1-9][0-9]* ops/sec' WT_TEST/test.stat
