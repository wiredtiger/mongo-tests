#!/bin/bash

function list_databases {
	sleep 1
	echo `/usr/bin/time -f "%e" ./mongo --quiet --eval "
		db.adminCommand({listDatabases:1});
	" 2>&1 >/dev/null`
}

function make_indexes {
	for i in {1..100}; 
	do
		name="abcd$(($1*100+$i))"
		./mongo $name --quiet --eval "
			db.$2.createIndex({x : 1});
			db.$2.insert({x:1});
			db.$3.createIndex({x : 1});
			db.$3.insert({x:1});
		" > /dev/null
	done
}

function drop_colls {
	for i in {1..100};
	do
	name="abcd$(($1*100+$i))"
		./mongo $name --quiet --eval "
			db.foo.drop();
			db.baz.drop();
			db.alpha.drop()
		" > /dev/null
	done
}

hits=0
# -> start mongo
for x in {1..100};
do
	coproc listdbfd { list_databases; }

	# Copy file descriptor
	exec 3>&${listdbfd[0]}

	make_indexes $x foo bar &
	make_indexes $x baz qux &
	make_indexes $x alpha beta &
	wait
	drop_colls $x
	FS= read -d '' -u 3 output
	if [ $output -ge 10 ]; then
		hhits=$((hits+1));
	fi
	sleep 5
done
# -> stop mongo
if [ $hits -gt 5 ]; then
	echo "We saw a $hits long running list databases";
	exit 1;
fi
