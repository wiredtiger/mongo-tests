#!/bin/bash
#
# TODO
#
set -x

usage () {
    cat << EOF
Usage: $0 mongodb_bin test_cfg [task]
Arguments:
    mongodb_bin  # Path to MongoDB binary
    test_cfg     # Test configuration
    task         # "clean-and-populate" to clean and populate
EOF
}

if [ $# -lt 2 ] || [ "$1" == "-h" ]; then
    usage
    exit
fi

MONGO_BIN=$1
TEST_CFG=$2

if [ "$3" == "clean-and-populate" ]; then
    echo "-- Cleaning and populating --"

    killall -9 mongod
    # Sleep to give mongodb time to close completely
    sleep 2
    rm -rf million-collection-test

    # Enabling populating phase if not required
    if grep -qi "populate=false" "$TEST_CFG"; then
        cp "$TEST_CFG" "$TEST_CFG".tmp
        TEST_CFG=$TEST_CFG.tmp
        echo forcing populate phase to false
        echo -e "\npopulate=true" >> "$TEST_CFG"
        TMP_FILE=$TEST_CFG
    fi
else
    echo "-- Using existing data --"

    # Disabling populating phase if required
    if ! grep -qi "populate=false" "$TEST_CFG"; then
        cp "$TEST_CFG" "$TEST_CFG".tmp
        TEST_CFG=$TEST_CFG.tmp
        echo forcing populate phase to false
        echo -e "\npopulate=false" >> "$TEST_CFG"
        TMP_FILE=$TEST_CFG
        exit
    fi
fi

# Clear the output of a previous run
rm -rf results
mkdir results

# Create folder if needed
mkdir -p million-collection-test
cd million-collection-test || exit
mkdir -p mkdir dbpath;

# Try to reuse existing mongod process
if pgrep -x "mongod" > /dev/null; then
    echo "-- Using already running mongod --"
else
    #WIREDTIGER_CONFIG="statistics=[all],statistics_log=(wait=1,json=true,on_close=true),file_manager=(close_handle_minimum=100,close_idle_time=30,close_scan_interval=30)," ${MONGO_BIN} -f ../largescale/mongod.conf
    if ! WIREDTIGER_CONFIG="statistics=[all],statistics_log=(wait=1,json=true,on_close=true)," ${MONGO_BIN} -f ../largescale/mongod.conf; then
        exit $?
    fi
fi

python3 ../largescale/many-collection-test.py "../$TEST_CFG"

# Save
cd ..
BAK_DIR="million-collection-test-$(date +%F-%H:%M)"
mkdir "$BAK_DIR"
mv results/ "$BAK_DIR"/.
cp -r million-collection-test/dbpath/diagnostic.data "$BAK_DIR"/.
mkdir "$BAK_DIR"/cfg
cp "$TEST_CFG" "$BAK_DIR"/cfg/.

# Clean temporary files
if [ ! -z "$TMP_FILE" ]; then
    rm "$TMP_FILE"
fi
