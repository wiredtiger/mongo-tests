#Readme for WT-2669

#Assumptions
* YCSB is setup and configured and you have set the $YCSB_BIN variable in run.sh
* We have network accesss to pull down software from git
* Python2.7 is the default system python and is capable of running the DSI suite

#Example run
## Step 1
Ensure mongodb binaries are available and the $MONGODIR and $MONGO_BASE variables are set
## Step 2
`sh run.sh --baseline`
This will gather the baseline for any evergreen performance comparisons. This can take considerable time, so please be paitent.

## Step 3
`sh run.sh`
This should generate output that looks like the following
```
Performing setup
Starting local worklaods
SERVER-23333
Run took: 593s
Test for SERVER-23333 failed
Error(s) from log were:
[js_test:SERVER-23333] 2016-06-15T02:52:25.956+0000 assert failed : Fragmentation is 29.335026443004608% of cache size, which exceeds threshold of 10%
[js_test:SERVER-23333] 2016-06-15T02:52:25.957+0000 2016-06-15T02:52:25.956+0000 E QUERY    [thread1] Error: assert failed : Fragmentation is 29.335026443004608% of cache size, which exceeds threshold of 10% :
Starting SERVER-20306
Run took: 1548s
Fragmentation over limit for test SERVER-20306. Max recorded fragmentation is 153
Starting SERVER-22906
Run took: 142s
Fragmentation over limit for test SERVER-22906. Max recorded fragmentation is 57
```

Note that the start of each run is listed and the highest recorded fragmentation value for said run is reported if this value exceeds the threshold.

Currently, the test suite is made up of 3 parts
* Local, which runs small shell/js tests and evaluates the fragmentation
* YCSB, which runs the YCSB workloads and evaluates the fragmentation
* Evergreen (EVG), which runs evergreen microbenchmarks and compares performance of the tested binaries to the baseline

#Options
Currently, you can provide the following options
`--suite=[local,ycsb,evg]` This will set a switch for which runs are being executed
`--baseline` This will gather a performance baseline in with the evg performance jobs 
`--compile` Compile mongodb from source, and use this version as the test binary
