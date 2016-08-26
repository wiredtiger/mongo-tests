MONGO_DIR=~/work/mongo
WT_DIR=~/work/wiredtiger
cd $MONGO_DIR
for t in `git tag --list | grep r3 | grep -v "\-rc"`; do
	cd $MONGO_DIR
	tag=`echo "mongodb-$t" | sed 's/r//'`
	git checkout $t > /dev/null 2>&1
	ref=`git log | egrep "^\s+Import wiredtiger" -A 8 -m 1 | grep ref: | sed 's/\s*ref: [0-9a-f]*\.\.//'`
	if [ "$ref" != "" ]; then
		cd $WT_DIR
		check=`git show --quiet --format="%h" $tag |tail -n 1`
		if [ "$check" != "" ]; then
			if [ "$check" != "$ref" ]; then
				echo "Tag $tag incorrect. Expected $ref got $check" 
			fi
		else
			git checkout $ref
			git tag -a $tag -m "MongoDB Release $tag"	
		fi
	fi
done
