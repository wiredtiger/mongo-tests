#! /usr/bin/env bash 
# 
# A script to help reproducing issue reported in HELP-7221 ticket.
#
# Ajusted to simulate inappropriate snapshotting by calling 
# “fsyncUnlock” followed by data write during snapshotting.
# 
set -u

DATA_VOL="vol-0ad36c971586de7ac"
JOURNAL_VOL="vol-0b36594c72cf4b510"
DATA_DIR="/data/single-rs"
JOURNAL_DIR="/journal"
MONGO_LOG="/home/ec2-user/mongodb.log"
MONGO_PORT="27017"
REPLICA_SET="single-rs"

take_volume_snapshot()
{
	volume=$1

	snapshot_id=$(aws ec2 create-snapshot --volume-id=$volume --description="HELP-7221" --output text --query "SnapshotId")
	echo -e "\nSnapshoting ${snapshot_id} (started)\n..."
#	snapshot_prog=$(aws ec2 describe-snapshots --snapshot-ids ${snapshot_id} --query "Snapshots[*].Progress" --output text)
#
#	finished=1
#	while [ $finished != "0" ]
#	do
#		aws ec2 describe-snapshots --snapshot-ids ${snapshot_id} --query "Snapshots[*].Progress" 
#		sleep 10
#		aws ec2 wait snapshot-completed --snapshot-ids "${snapshot_id}"
#		finished="$?"
#	done
#
#	echo "Snapshoting ${snapshot_id} (finished)"
}


# Kill mongod process if it exists
rtn=$(pgrep mongod)
if [ ! -z "$rtn" ]; then
	echo "Killing mongod process ..."
	pkill -9 mongod
fi

# Clean up data directory before restarting mongod
rm -rf ${JOURNAL_DIR}/*
rm -rf ${DATA_DIR}/*

# Create symlink to make journals stored in a separate partition
ln -s /journal ${DATA_DIR}/journal

# Start mongod process
mongod 	--fork --logpath ${MONGO_LOG} --replSet ${REPLICA_SET} --port ${MONGO_PORT} --dbpath ${DATA_DIR}

# Initiate the replicate set
mongo --eval 'rs.initiate()'
# Give the replica set some time to settle
sleep 5


if [ ! -d mongo ]; then
	git clone https://github.com/mongodb/mongo
fi

cd mongo 

# Insert data using jstests library
echo -e "\nInsert data into the database (started)\n..."
tests=$(find jstests/core/ -name index\*| head -30)
for test in $tests 
do 	
	mongo $test > /dev/null 
done 
echo "Insert data into the database (finished)"

# Call fsyncLock 
echo -e "\nCall fsyncLock (started)\n..."
mongo --eval "db.getSiblingDB('admin').fsyncLock()"
echo "Call fsyncLock (finished)"

# Create EBS volume snapshots for both data and journal volumes
take_volume_snapshot ${DATA_VOL}
take_volume_snapshot ${JOURNAL_VOL}

# Call fsyncUnlock
echo -e "\nCall fsyncUnlock (started)\n..."
mongo --eval "db.getSiblingDB('admin').fsyncUnlock()"
echo "Call fsyncUnlock (finished) " 

# Insert data using jstests library
echo -e "\nInsert data into the database (started)\n..."
tests=$(find jstests/core/ -name index\*| tail -30)
for test in $tests 
do 	
	mongo $test > /dev/null 
done 
echo "Insert data into the database (finished)"
