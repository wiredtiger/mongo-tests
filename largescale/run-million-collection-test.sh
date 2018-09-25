#! /usr/bin/env bash
# 
# A script to prepare test environment and execute million collections testing.
# 

set -eux

MONGO_REPO="https://github.com/mongodb/mongo"
MONGO_TESTS_REPO="https://github.com/wiredtiger/mongo-tests"
POCDRIVER_REPO="https://github.com/wiredtiger/POCDriver"
POCDRIVER_BRANCH="mongodb-million-collections"
TEST_DIR="mongo-million-collection-test"
PERF_MAKE_FLAGS="-j 20"

function prepare_test_env() { 
	# Backup the old test directory if found
	if [ -d ${TEST_DIR} ]; then
		mv ${TEST_DIR} ${TEST_DIR}_$(date +%F-%H:%M)
	fi

	# Clone the mongo repo as the top test directory
	git clone ${MONGO_REPO} ${TEST_DIR} || exit $?

	# Clone other repos inside the test directory
	cd ${TEST_DIR}
	git clone -b million-collect-test-evg ${MONGO_TESTS_REPO} || exit $?

	# Copy POCDriver.jar over from mongo-tests local repo
	mkdir -p POCDriver/bin
	cp mongo-tests/largescale/POCDriver.jar POCDriver/bin/

	#git clone -b ${POCDRIVER_BRANCH} ${POCDRIVER_REPO} || exit $?
	# Build from the POCDriver repo
	#( cd POCDriver && mvn clean package )

	# Setup directory to record test output
	if [ -d "results" ]; then
		rm -rf results
	fi
	mkdir results
}

function merge_wiredtiger_develop() { 
	(cd src/third_party
	curl -OJL https://api.github.com/repos/wiredtiger/wiredtiger/tarball/develop
	tarball=$(echo wiredtiger-wiredtiger-*.tar.gz)
	test -f "${tarball}"
	mkdir -p wiredtiger
	(cd wiredtiger;
	 rm -rf *;
	 git checkout -- .gitignore 'SCons*';
	 git checkout -- 'build_*/wiredtiger_config.h')
	tar -x --strip-components 1 \
	    --exclude '*/api' --exclude '*/dist/package' --exclude '*/examples' \
	    --exclude '*/src/docs' --exclude '*/test' \
	    --exclude '*/tools/wtperf_stats' \
	    --exclude '*/tools/wtstats/template' \
	    -C wiredtiger -f ${tarball}
	)
}

function build_mongod() { 
	sudo pip install -r buildscripts/requirements.txt
	python buildscripts/scons.py CC=/opt/mongodbtoolchain/v2/bin/gcc CXX=/opt/mongodbtoolchain/v2/bin/g++ ${PERF_MAKE_FLAGS} mongod || exit $?
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
	cd mongo-tests
	python largescale/run-test.py largescale/config/million-collection-testing | tee ../results/results.txt
	exit ${PIPESTATUS[0]}
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
