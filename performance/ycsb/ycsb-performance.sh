WORKLOAD_DIR=./mongo-tests/performance/ycsb/workloads
MONGODB_CONFIG_DIR=./mongo-tests/performance/ycsb/config
DATA_DIR=./data
LOG_DIR=./logs
OUTPUT_DIR=./output
YCSB_BIN=/home/ec2-user/ycsb/bin
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
    pkill python
    pkill java
    sleep 3
    rm -rf $DATA_DIR/*
    #mkdir $DATA_DIR
}

# reset_mongo config_filepath workload_name
function reset_mongo
{
    cleanup
    sleep 3
    echo "starting mongod with config $1"
    /home/ec2-user/mongo/mongod --config $1 --dbpath $DATA_DIR --logpath $LOG_DIR/$2.log --fork 
}

function output_totals
{
    run_time=`grep "\[OVERALL\], RunTime" $OUTPUT_DIR/$1 | awk '{ print $3}'`
    throughput=`grep "\[OVERALL\], Throughput" $OUTPUT_DIR/$1 | awk '{ print $3}'`
    echo "YVALUE=$run_time" > $OUTPUT_DIR/$1-run_time.properties
    echo "YVALUE=$throughput" > $OUTPUT_DIR/$1-throughput.properties
}

#run_ycsb workload_filepath workload_name action
function run_ycsb
{
    echo "$3 dataset $2 from $1"
    start=`date +%s`
    $YCSB_BIN/ycsb $3 mongodb -s -P $1 &> $OUTPUT_DIR/$2-$3
    end=`date +%s`
    echo $(($end-$start)) > $OUTPUT_DIR/$2.time
    print_stats ${workload_name}-$3 $OUTPUT_DIR/$2-$3
    output_totals $2-$3
}

mkdir $LOG_DIR $OUTPUT_DIR

shopt -s nullglob
for dataset in ${WORKLOAD_DIR}/*
do
    for compressor in lz4 bzip2 zlib snappy none
    do
        workload_name=stdcfg-$(basename $dataset)-$compressor
        sed -i "s/      blockCompressor:.*/      blockCompressor: $compressor/" $MONGODB_CONFIG_DIR/$(basename $dataset)
        reset_mongo $MONGODB_CONFIG_DIR/$(basename $dataset) $workload_name

        # If the dataset is a one-off then load it and run it
        if [ ! -d $dataset ]; then
            run_ycsb $dataset $workload_name load
            run_ycsb $dataset $workload_name run
        else
            # The dataset is a directory of various workloads
            needs_load=true
            for workload in ${dataset}/*
            do
                workload_name=stdcfg-$(basename $dataset)-$(basename $workload)
                # Load the data for the first workload file
                if [ "$needs_load" = true ]; then
                    run_ycsb $workload $workload_name load
                    needs_load=false
                fi
        
                run_ycsb $workload $workload_name run
            done
        fi
        echo "data size for $worload_name was `du -sh $DATA_DIR`" > $OUTPUT_DIR/$workload_name.size
        echo "log  size for $worload_name was `du -sh $DATA_DIR/journal`" >> $OUTPUT_DIR/$workload_name.size
    done
done

cleanup

