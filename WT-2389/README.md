#Readme for WT-2389

#Usage
## testExecStatGen.sh:
./testExecStatGen.sh <wtperf-conf/WT_TEST-dir> <opt-scale> <opt-mins-discard>
This extracts "bytes written from cache" data from the statistics generated with
a wtperf workload and creates a histogram representing it. If provided with a
wtperf configuration file it executes the test as well.

## compareRuns.sh:
./compareRuns.sh <histogram-output-1> <histogram-output-2> <optional-width>
This compares two histogram outputs generated with testExecStatGen.sh.i To
compare more than two histograms, directly use the command:
pr -m -t <file1> <file2> <file3> .. -w <width>

#Example run
## Step 1
Change to build_posix/bench/wtperf directory

## Step 2
`./wtperf -O create_phase.wtperf -o verbose=2`
This will create the database tables and populate data for the update phase

## Step 3
`sh testExecStatGen.sh update_phase.wtperf`
This will run wtperf with update_phase.wtperf configuration and generate
histogram like the following
```
Stats : bytes written from cache
==================================
Avg:450 MBps
Max:702 MBps
Min:0 Bps
 
Histogram:
==========
BucketSize:28 MBps
Histogram Scale factor:1
 
   %age Max
  ==========
    0 -   4 : == 
    4 -   8 : === 
    8 -  12 : ============ 
   12 -  16 : = 
   16 -  20 :  
   20 -  24 : = 
   24 -  28 : = 
   28 -  32 : = 
   32 -  36 : == 
   36 -  40 : = 
   40 -  44 : = 
   44 -  48 : = 
   48 -  52 : = 
   52 -  56 : ===== 
   56 -  60 : ========================= 
   60 -  64 : ====================================================== 
-> 64 -  68 : ==================================== 
   68 -  72 : ================= 
   72 -  76 : ============ 
   76 -  80 : ===== 
   80 -  84 : ======== 
   84 -  88 : ======== 
   88 -  92 : ============ 
   92 -  96 : ==================== 
   96 - 100 : ========= 
 
Executed 0 read operations (0%) 0 ops/sec
Executed 0 insert operations (0%) 0 ops/sec
Executed 0 truncate operations (0%) 0 ops/sec
Executed 11374430 update operations (100%) 18957 ops/sec
Executed 5 checkpoint operations
```

## Step 4
`sh compareRuns.sh run1/statAnalysis.op run2/statAnalysis.op 120`
This will compare output from step 3 for two different runs. Optionally provide
a width (120 in the example) for adjusting the displacement between the two
files provided.

#Options
Currently, you can provide the following options
`./testExecStatGen.sh <wtperf-conf>` This will run wtperf with the given
configuration file and generate histogram from the obtained statistics file
`./testExecStatGen.sh <WT_TEST-dir>` This will look for the statistics file in
the directory provided and generate histogram from it.
`./testExecStatGen.sh <wtperf-conf> <opt-scale> <opt-mins-discard>` Optionally
provide a scaling factor for the histogram (defaults to 1) and provide minutes
to shave off from the stats (defaults to 2 mins)

