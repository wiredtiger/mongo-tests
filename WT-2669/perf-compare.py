#!/usr/bin/env python
import sys, re

# Do a performance outputs analysis
# Block format:
# Update.SetWithMultiIndex.String
# 1       18632.8733179406
# 8       68195.8029875472
def analyse_perf(name, f, one, eight):
    f.seek(0)
    failed = False 
    while True:
        line = f.readline()
        if not line: break
        if re.match(name, line):
            one_c = float(str.split(f.readline())[1])
            eight_c = float(str.split(f.readline())[1])
            if one * 0.9 > one_c:
                print "Test of " + name + " 1-thread failed."
                print "Comparing " + str(one_c) + " and " + str(one)
                failed = True
            if eight * 0.9 > eight_c:
                print "Test of " + name + " 8-thread failed ."
                print "Comparing " + str(eight_c) + " and " + str(eight)
                failed = True
    return failed

# Do a sys-perf line's perf analysis
# Line format: >>> insert_capped : 119774.19719469387 1
def analyse_sysperf(name, f):
    split = str.split(name)
    failed = False
    f.seek(0)
    for line in f:
        if re.search(split[1], line):
            split_c = str.split(line)
            if split_c[4] == split[4]:
                if float(split[3]) * 0.9 > float(split_c[3]):
                    print "Test of " + split[1] + " " + split[4] + "-thread failed."
                    print "Comparing " + split_c[3] + " and " + split[3]
                    failed = True
    return failed

# Main
if len(sys.argv) != 3:
    print "usage: " + sys.argv[0] + " baseline.out run.out"
    exit(1)

baseline_file = sys.argv[1]
perf_run_file = sys.argv[2]

baseline = open(baseline_file, 'r')
perf_run = open(perf_run_file, 'r')

failed = False

while True:
    line = baseline.readline()
    if not line: break
    # Match lines to which perf system they are from 
    if re.match("^>>>", line) is not None:
       failed = (failed|analyse_sysperf(line, perf_run))
    elif re.match("^\d+\s+\d+", line) is not None:
        continue
    else:
        one = float(str.split(baseline.readline())[1])
        eight = float(str.split(baseline.readline())[1])
        failed = (failed|analyse_perf(line, perf_run, one, eight))

baseline.close()
perf_run.close()
if failed:
    exit(1)
