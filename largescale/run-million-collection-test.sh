#! /usr/bin/env bash
# 
# A script to prepare test environment and execute million collections testing.
# 

set -ux

MONGO_REPO="https://github.com/mongodb/mongo"
MONGO_TESTS_REPO="https://github.com/wiredtiger/mongo-tests"
POCDRIVER_BRANCH="mongodb-million-collections"
TEST_DIR="mongo-million-collection-test"
PERF_MAKE_FLAGS="-j 20"

# Use mongodbtoolchain Python binary when possible
if [ -f /opt/mongodbtoolchain/v3/bin/python3 ]; then 
	PYTHON="/opt/mongodbtoolchain/v3/bin/python3"
else
	PYTHON="python3"
fi

function prepare_test_env() { 
	# Backup the old test directory if found
	if [ -d ${TEST_DIR} ]; then
		mv ${TEST_DIR} ${TEST_DIR}_$(date +%F-%H:%M)
	fi

	# Clone the mongo repo as the top test directory
	git clone ${MONGO_REPO} ${TEST_DIR} || exit $?

	# Clone other repos inside the test directory
	cd ${TEST_DIR}
	pip install loremipsum

	cd ../../wiredtiger/
	commit_date=`git log --pretty=format:"%cd" --date=iso -1`
	echo $commit_date
	cd -

	git checkout `git rev-list -n 1 --first-parent --before="$commit_date" master`
	# Install required modules
	${PYTHON} -m pip install -r buildscripts/requirements.txt

	git clone ${MONGO_TESTS_REPO} || exit $?

	# Copy POCDriver directory over from mongo-tests local repo
	cp -r mongo-tests/largescale/POCDriver . 

	# Setup directory to record test output
	if [ -d "results" ]; then
		rm -rf results
	fi
	mkdir results
}

function merge_wiredtiger_develop() {
	echo "Printing head of wiredtiger log to confirm version."
	cd ../../wiredtiger/
	git log -1
	cd -
	echo "Copying in wiredtiger source using command: cp -a ../../wiredtiger/. src/third_party/wiredtiger/"
	cp -a ../../wiredtiger/. src/third_party/wiredtiger/
}

function build_mongod() { 
	${PYTHON} buildscripts/scons.py --variables-files=etc/scons/mongodbtoolchain_stable_gcc.vars ${PERF_MAKE_FLAGS} mongod || exit $?
}

function start_mongod(){
	# Kill running mongod processes if any
	killall mongod || true

	# Recreate dbpath directory
	if [ -d "dbpath" ]; then
		rm -rf dbpath
	fi
	mkdir dbpath

	# Start mongod process
	./mongod -f mongo-tests/largescale/mongod.conf 
}

function start_million_collection_test() {
	# Install required packages 
	sudo yum install java-1.8.0 -y

	cd mongo-tests
	python largescale/run-test.py largescale/config/million-collection-testing | tee ../results/results.txt
	exit_code=${PIPESTATUS[0]}
	cd ../../
	exit ${exit_code}
}

function main() { 
	prepare_test_env
	merge_wiredtiger_develop
	build_mongod
	start_mongod
	start_million_collection_test
}

if [ $# -ne 1 ]; then
	echo "Usage: $0 <dir_to_run_test>"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "$1 does not exist" 
fi 

cd $1

main
