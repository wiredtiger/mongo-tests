#! /usr/bin/env bash 
# 
# A script to help reproducing issue reported in HELP-7221 ticket.
# 
set -u

DATA_VOL="vol-0ad36c971586de7ac"
JOURNAL_VOL="vol-0b36594c72cf4b510"
DATA_DIR="/data/single-rs"
MONGO_LOG="/home/ec2-user/mongodb.log"
MONGO_PORT="27017"
REPLICA_SET="single-rs"

take_volume_snapshot()
{
	volume=$1

	snapshot_id=$(aws ec2 create-snapshot --volume-id=$volume --description="HELP-7221" --output text --query "SnapshotId")
	snapshot_prog=$(aws ec2 describe-snapshots --snapshot-ids ${snapshot_id} --query "Snapshots[*].Progress" --output text)

	finished=1
	while [ $finished != "0" ]
	do
		echo -e "\nSnapshoting ${snapshot_id} (started)\n..."
		aws ec2 describe-snapshots --snapshot-ids ${snapshot_id} --query "Snapshots[*].Progress" 
		sleep 10
		aws ec2 wait snapshot-completed --snapshot-ids "${snapshot_id}"
		finished="$?"
	done

	echo "Snapshoting ${snapshot_id} (finished)"
}


if [ ! $(which mongod) ]; then 
	echo "Make sure mongod binary is installed properly ..."
	exit 1 
fi 

# Kill mongod process if it exists
rtn=$(pgrep mongod)
if [ ! -z "$rtn" ]; then
	echo "Killing mongod process ..."
	pkill -9 mongod
fi

# Clean up data directory before restarting mongod
rm -rf ${DATA_DIR}/

# Create symlink to make journals stored in a separate partition
mkdir -p ${DATA_DIR}/journal
ln -s /journal ${DATA_DIR}/journal

# Start mongod process
mongod 	--fork --logpath ${MONGO_LOG} --replSet ${REPLICA_SET} --port ${MONGO_PORT} --dbpath ${DATA_DIR}

# Initiate the replicate set
mongo --eval 'rs.initiate()'
# Give the replica set some time to settle
sleep 10


if [ ! -d mongo ]; then
	git clone https://github.com/mongodb/mongo
fi

cd mongo 

# Insert data using jstests library
echo -e "\nInsert data into the database (started)\n..."
tests=$(find jstests/core/ -name index\*)
for test in $tests 
do 	
	mongo $test > /dev/null 
	#mongo $test 
done 
echo "Insert data into the database (finished)"

# Call fsyncLock 
echo -e "\nCall fsyncLock (started)\n..."
#date
mongo --eval "db.getSiblingDB('admin').fsyncLock()"
echo "Call fsyncLock (finished)"
#date

# Create EBS volume snapshots for both data and journal volumes
take_volume_snapshot ${DATA_VOL}
take_volume_snapshot ${JOURNAL_VOL}

# Call fsyncUnlock
echo -e "\nCall fsyncUnlock (started)\n..."
#date
mongo --eval "db.getSiblingDB('admin').fsyncUnlock()"
echo "Call fsyncUnlock (finished) " 
#date
