#!/usr/bin/env bash
#
# In order to reduce footprint of those Jenkins perf job archives, we need to compress those archive directories 
# We did not apply the Compress Artifacts plugin because it does not work well with the Archive Artifacts plugin,
# which are used by some Jenkins jobs.
#
# Refer to BUILD-4554 for details.
#

JENKINS_JOB_DIR="/home/jenkins/jenkins/jobs/"

JENKINS_JOB_LIST=(
	'wiredtiger-perf-lsm'
	'wiredtiger-perf-long'
	'wiredtiger-perf-btree'
	'wiredtiger-perf-evict'
	'wiredtiger-perf-stress'
	'wiredtiger-perf-checkpoint'
	'wiredtiger-perf-log-consolidated'
	'wiredtiger-test-race-condition-stress-sanitizer'
)

NUM_DAYS_LOOK_BACK=5


# Record the timestamp when the script is triggered to run
echo
echo
echo "################################"
date
echo "################################"

cd $JENKINS_JOB_DIR

for job in "${JENKINS_JOB_LIST[@]}"
do 
	echo
	echo "====== job: $job ======"
	cd $job/builds/
 
	for build in $(find -maxdepth 1 -type d -mtime -${NUM_DAYS_LOOK_BACK} -regextype sed -regex ".*/[[:digit:]]\{1,\}")
	do 
		cd $build

		# tar and compress the 'archive' directory if it exists
		if [ -d archive ]; then 
			echo
			echo "[dir]: $(pwd)"
			tar cvfz archive.tar.gz --remove-files archive
		fi

		cd ..
	done

	cd ../..
done
