WORKLOAD_DIR=./mongo-tests/performance/ycsb/workloads
MONGODB_CONFIG_DIR=./mongo-tests/performance/ycsb/config
DATA_DIR=./data
LOG_DIR=./logs
OUTPUT_DIR=./output
YCSB_BIN=./ycsb/bin
STATS_FILE=./result-stats.txt

# scrape_stat metric phase file
function scrape_stat
{
    echo $(grep $1 $3 | grep "\[$2\]" | awk '{print $3}')
}

# print_stats workload_name file
function print_stats
{
    for phase in INSERT UPDATE READ SCAN READ-MODIFY-WRITE
    do
        if [ $(grep "\[${phase}\]" $2 | wc -l) -gt 0 ]; then
            printf "%s\t%s\t%s\t%s\n" $1-${phase} \
                $(scrape_stat "AverageLatency" $phase $2) \
                $(scrape_stat "MaxLatency" $phase $2) \
                $(scrape_stat "99thPercentileLatency" $phase $2) \
                >> $STATS_FILE
        fi
    done

    phase=OVERALL
    printf "%s\t%s\t%s\n" $1-${phase} \
        $(scrape_stat "RunTime" $phase $2) \
        $(scrape_stat "Throughput" $phase $2) \
        >> $STATS_FILE
}

function cleanup
{
    killall -9 mongod
    rm -rf $DATA_DIR
    mkdir $DATA_DIR
}

# reset_mongo config_filepath workload_name
function reset_mongo
{
    cleanup
    sleep 3
    echo "starting mongod with config $1"
    ./mongod --config $1 --dbpath $DATA_DIR --logpath $LOG_DIR/$2.log --fork >& /dev/null
}

#run_ycsb workload_filepath workload_name action
function run_ycsb
{
    echo "$3 dataset $2 from $1"
    $YCSB_BIN/ycsb $3 mongodb -s -P $1 -p recordcount=1000 -p operationcount=10000 &> $OUTPUT_DIR/$2-$3
    print_stats ${workload_name}-$3 $OUTPUT_DIR/$2-$3 
}

mkdir $LOG_DIR $OUTPUT_DIR

shopt -s nullglob
for config in ${MONGODB_CONFIG_DIR}/*
do
    for dataset in ${WORKLOAD_DIR}/*
    do
        workload_name=$(basename $config)-$(basename $dataset)
        reset_mongo $config $workload_name
        
        if [ ! -d $dataset ]; then
            run_ycsb $dataset $workload_name load
            run_ycsb $dataset $workload_name run
        else
            needs_load=true
            for workload in ${dataset}/*
            do
                workload_name=$(basename $config)-$(basename $dataset)-$(basename $workload)
                # load the data for the first workload file
                if [ "$needs_load" = true ]; then
                    run_ycsb $workload $workload_name load
                    needs_load=false
                fi
            
                run_ycsb $workload $workload_name run       
            done
        fi    
    done
done

cleanup

