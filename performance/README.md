## Running Performance Tests

These performance tests use a set of mongodb configurations and YCSB workloads to measure the effects of code changes to performance over time.

For setting up a new machine to run the tests, see [bootstrap.sh] as an example, this script performs the following :

* clones mongodb
* merges changes from WiredTiger develop branch
* pulls this repo and extracts performance tests
* pulls YCSB and builds it
* runs the YCSB tests using [ycsb/ycsb-performance.sh]

The [ycsb-performance.sh](ycsb/ycsb-performance.sh) script has a number of variables at the top which will work when setup via [bootstrap.sh](bootstrap.sh),
however these allow configuration of the YCSB installation path and data/log/output directories if desired.

## MongoDB configuration

The [ycsb-performance.sh](ycsb/ycsb-performance.sh) script runs the suite of ycsb workloads for each MongoDB configuration in the [config directory](ycsb/config). For each config, it will delete the data directory, restart mongod and run all of the workloads found in the [workload directory](ycsb/workloads). 

## Workloads

The [workload directory](ycsb/workloads) is processed as follows :

* **Files** will be treated as workload files and both YCSB *load* and *run* phases will be executed for each
* **Directories** will be considered as a goup of workloads to be run against a single dataset. The first workload file in each directory will be used to perform the *load* phase and the *run* phase will be executed on all files in that directory. This is a useful feature for running multiple workload profiles (e.g. 80/20, 50/50, 20/80 READ/UPDATE etc) over a large dataset without having to reload each time.

## Output

There are *output* and *logs* directories created by the script that will contain the raw YCSB output and mongod logs respectively. 

In addition, a summary *result-stats.txt* file will be created containing summary performance stats from each of the YCSB runs. Each line begins with a concatenation of the config, dataset, workload and phase (READ, UPDATE etc) followed by tab separated values for AverageLatency(us), MaxLatency(us) and 99thPercentileLatency(ms). In addition, for each workload load/run, an *OVERALL* entry is created followed by values for Runtime(ms) and Throughput(ops/sec).


