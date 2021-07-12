#!/bin/bash
#
# A script to prepare test environment and execute many collections testing.
#

usage () {
    cat << EOF
Usage: $0 mongodb_bin mongo_logs test_cfg output [task]
Arguments:
    mongodb_bin # MongoDB binary
    mongo_logs  # MongoDB logs
    test_cfg    # Test configuration
    output      # Output directory, the current date will be appended to the name
    task        # "clean-and-populate" to clean and populate
EOF
}

if [ $# -lt 3 ] || [ "$1" == "-h" ]; then
    usage
    exit
fi

MONGO_BIN=$1
MONGO_LOG=$2
TEST_CFG=$3
OUTPUT=$4
TASK=$5

if [ "$TASK" == "clean-and-populate" ]; then
    echo "-- Cleaning and populating --"

    killall -9 mongod
    # Sleep to give mongodb time to close completely
    sleep 2
    rm -rf "$OUTPUT"

    # Enabling populating phase if missing in the test configuration
    if grep -qi "populate=false" "$TEST_CFG"; then
        cp "$TEST_CFG" "$TEST_CFG".tmp
        TEST_CFG=$TEST_CFG.tmp
        echo forcing populate phase to true
        echo -e "\npopulate=true" >> "$TEST_CFG"
        TMP_FILE=$TEST_CFG
    fi
else
    echo "-- Using existing data --"
    # Check for existing data
    if [ ! -d "$OUTPUT"/dbpath ]; then
        echo "$OUTPUT"/dbpath does not exist ! No existing data can be reused.
        echo Use the "clean-and-populate" task to generate a database.
        echo FAILED
        exit 1
    fi

    # Disabling populating phase if missing in the test configuration
    if ! grep -qi "populate=false" "$TEST_CFG"; then
        cp "$TEST_CFG" "$TEST_CFG".tmp
        TEST_CFG=$TEST_CFG.tmp
        echo forcing populate phase to false
        echo -e "\npopulate=false" >> "$TEST_CFG"
        TMP_FILE=$TEST_CFG
    fi
fi

# Clear the output of a previous run
rm -rf results
mkdir results

# Create folder if needed
mkdir -p "$OUTPUT"
cd "$OUTPUT" || exit 1
mkdir -p dbpath;

# Try to reuse existing mongod process
if pgrep -x "mongod" > /dev/null; then
    echo "-- Using already running mongod --"
else
    if ! ../"$MONGO_BIN" -f ../mongod.conf --logpath "$MONGO_LOG"; then
        exit $?
    fi
fi

python3 ../many-collection-test.py ../"$TEST_CFG"

ERROR=$?

# Check for start up and shut down time if required.
ENABLE_CHECK=$(grep "enable_stats_check" ../"$TEST_CFG" | cut -d = -f 2)
if [ "$ENABLE_CHECK" == "true" ]; then
    kill "$(pgrep mongod)"

    # If we are using an existing mongod process, we need to start looking from the last
    # "SERVER RESTARTED" message in the logs.
    if [ "$TASK" == "clean-and-populate" ]; then
        LAST_RESTART=0
    else
        LAST_RESTART=$(grep -n "SERVER RESTARTED" "$MONGO_LOG"  | tail -1 | cut -d : -f 1)
    fi

    # Timeout before exiting the script if WT takes too long to stop.
    TIMEOUT=3600
    ELAPSED_TIME=0
    echo Waiting for mongod to stop...
    until [ "$ELAPSED_TIME" -ge "$TIMEOUT" ] || tail -n +"$LAST_RESTART" "$MONGO_LOG" | grep "WiredTiger closed" > /dev/null;
    do
        sleep 1
        ((ELAPSED_TIME=ELAPSED_TIME+1))
        echo time elapsed... "$ELAPSED_TIME"s
    done

    STARTUP_TIME=$(grep "WiredTiger opened" "$MONGO_LOG" | tail -1 | awk '{print $5}' | grep -Eo '[0-9]{1,}')
    STARTUP_TIME_THRESHOLD=$(grep "max_startup_time" ../"$TEST_CFG" | grep -Eo '[0-9]{1,}')
    echo WT took "$STARTUP_TIME" ms to start up
    if [ "$STARTUP_TIME" -ge "$STARTUP_TIME_THRESHOLD" ]; then
        echo "Startup time took too long: $STARTUP_TIME ms (max allowed: $STARTUP_TIME_THRESHOLD ms)"
        ERROR=1
    fi

    if [ "$ELAPSED_TIME" -ge "$TIMEOUT" ]; then
        echo WT took more than "$TIMEOUT"s to shut down. Forcing script to exit...
        ERROR=1
    else
        SHUTDOWN_TIME=$(grep "WiredTiger closed" "$MONGO_LOG" | tail -1 | awk '{print $5}' | grep -Eo '[0-9]{1,}')
        SHUTDOWN_TIME_THRESHOLD=$(grep "max_shutdown_time" ../"$TEST_CFG" | grep -Eo '[0-9]{1,}')
        echo WT took "$SHUTDOWN_TIME" ms to shut down
        if [ "$SHUTDOWN_TIME" -ge "$SHUTDOWN_TIME_THRESHOLD" ]; then
            echo "Shutdown time took too long: $SHUTDOWN_TIME ms (max allowed: $SHUTDOWN_TIME_THRESHOLD ms)"
            ERROR=1
        fi
    fi
fi

# Save generated files
cd ..
BAK_DIR="$OUTPUT"-"$(date +%F-%H:%M:%S)"
mkdir -p "$BAK_DIR"
mv results/ "$BAK_DIR"/.
cp -r "$OUTPUT"/dbpath/diagnostic.data "$BAK_DIR"/.
mkdir -p "$BAK_DIR"/cfg
cp "$TEST_CFG" "$BAK_DIR"/cfg/.

# Clean temporary files
if [ -n "$TMP_FILE" ]; then
    rm "$TMP_FILE"
fi

if [[ $ERROR -ne 0 ]]; then
    echo FAILED
    exit 1
fi

echo SUCCESS
