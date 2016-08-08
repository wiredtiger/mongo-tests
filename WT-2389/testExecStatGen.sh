#!/bin/sh

# Usage: sh testExecStatGen.sh <wtperf config-file/test-dir> <optional-histogram-scale> <optional-discard-first-n-mins>
# Run from the build_posix/bench/wtperf/ directory
# Runs the wtperf workload given and does analysis of the bytes written from
# cache.

ceildiv() { echo $((($1+$2-1)/$2));}

if [ $# -eq 0 ]; then
	echo "No arguments provided"
	echo "Usage:"
	echo "  \"./${0##*/} <path-to-wtperf-config-file> \"  - Runs given wtperf config and generates analysis"
	echo "                                                  OR"
	echo "  \"./${0##*/} <path-to-wtperf-test-dir>\"  - Generates analysis from given wtperf test dir"
	echo " "
	echo "  \"./${0##*/} <conf-file/test-dir> <optional-histogram-scale> <optional-discard-first-n-mins>\""
	echo "              - Optionally give a histogram scaling factor (default 1), optionally give \"n\" minutes to discard (2 by default) "
        exit 1
fi

scale=1
if [ $# -eq 2 ]; then
	scale=$2
fi

discard_mins=2
if [ $# -eq 3 ]; then
	discard_mins=$3
fi

WTPERFDIR=""
echo " "

if [ -d "$1" ] ; then
	WTPERFDIR=$1
else
	if [ -f "$1" ]; then
		enable_delay=0
		tmp_count=`grep -c "wait=" $1`
		if [ $tmp_count -eq 0 ]; then
			echo "Warning: Need to have statistics enabled in configuration."
			echo " "
			enable_delay=1
		else
			tmp_count=`grep -o 'wait=[0-9]*' $1 | cut -d'=' -f2`
			if [ $tmp_count -eq 0 ]; then
				echo "Warning: Need to have statistics enabled in configuration."
				echo " "
				enable_delay=1
			fi
		fi

		if [ $enable_delay -eq 1 ]; then
			sleep 2
		fi

		mkdir -p WT_TEST/
		./wtperf -O $1 -o verbose=2
		WTPERFDIR="WT_TEST"
	else
		echo "$1 doesn't exist or isn't valid";
	        exit 1
	fi
fi

# Create a new test directory and copy test data there
TESTDIR=test-`date +%m_%d_%H_%M_%S`
mkdir $TESTDIR

cp $WTPERFDIR/*.wtperf $TESTDIR/
cp $WTPERFDIR/*.stat $TESTDIR/
cat $WTPERFDIR/WiredTigerStat.* > $TESTDIR/WiredTigerStat.concat

echo " "
echo "Collecting Stats and Running Analysis.."
echo "Stats Directory : $TESTDIR"

# Run analysis on the stats collected
TESTOPFILE="$TESTDIR/statAnalysis.op"
WTSTATFILE="$TESTDIR/WiredTigerStat.concat"
TESTSTATFILES="$TESTDIR/*.stat"
BUCKETS=25

TMPSORTEDFILE="$TESTDIR/.__tmp.sorted"
TMPRANGEOPFILE="$TESTDIR/.__tmp.range.op"
TMPSTATFILE="$TESTDIR/.__tmp.stat"

# Get the wait value issued
WAIT_VAL=`grep -o 'wait=[0-9]*' $TESTDIR/*.wtperf | head -1 | cut -d'=' -f2`

# Check if clear statistics are set, default to not set
CLEAR_SET=`grep statistics $TESTDIR/*.wtperf | grep clear -c | head -1`

# Check if collecting in json format
JSON_SET=`grep -c "json=1" $TESTDIR/*wtperf | head -1`

# Separate the stats needed
if [ $JSON_SET -eq 0 ]; then
	grep "WT_TEST cache: bytes written from cache" $WTSTATFILE | cut -d" " -f4 > $TMPSTATFILE
else
	grep -o '"bytes written from cache":[0-9]*' $WTSTATFILE | cut -d':' -f2 > $TMPSTATFILE
fi

if [ $CLEAR_SET -eq 0 ]; then
	# Create stats that do not cumulate over previous entry
	DIFFTMPFILE="$TESTDIR/.__tmp.diff"
	: > $DIFFTMPFILE

	prevVal=0
	while read p; do
		diff=$((p-prevVal))
		echo "$diff" >> $DIFFTMPFILE
		prevVal=$p
	done < $TMPSTATFILE

	mv $DIFFTMPFILE $TMPSTATFILE
fi

#Remove first n mins if specified
if [ $discard_mins -ne 0 ]; then
	discard_lines=$((discard_mins*60))
	discard_lines=$((discard_lines/WAIT_VAL))
	sed -i -e 1,"$discard_lines"d $TMPSTATFILE
fi

# Sort the stats
sort -n $TMPSTATFILE > $TMPSORTEDFILE

count=0
sum=0
max=0
min=`head -1 $TMPSORTEDFILE`
while read p; do
	sum=$((sum += p))
	count=$((count += 1))
	if [ "$p" -gt "$max" ]
       	then
		max=$p
	fi
	if [ "$p" -le "$min" ]
       	then
		min=$p
	fi
done < $TMPSORTEDFILE
avg=$((sum/count))

# Divide by wait=x factor
avg_reported=$((avg/WAIT_VAL))
max_reported=$((max/WAIT_VAL))
min_reported=$((min/WAIT_VAL))

: > $TESTOPFILE

echo " "
echo "Stats : bytes written from cache" >> $TESTOPFILE 
echo "==================================" >> $TESTOPFILE
echo "Avg:$((avg_reported/1000000)) MBps" >> $TESTOPFILE
echo "Max:$((max_reported/1000000)) MBps" >> $TESTOPFILE
echo "Min:$min_reported Bps" >> $TESTOPFILE
echo " " >> $TESTOPFILE
echo "Histogram:" >> $TESTOPFILE
echo "==========" >> $TESTOPFILE

# Generate Range divided in No of buckets
rangeMax=$max
#bucketSize=$((rangeMax/$BUCKETS))
bucketSize=$( ceildiv rangeMax $BUCKETS )
bucketSize_reported=$((bucketSize/WAIT_VAL))

echo "BucketSize:$((bucketSize_reported/1000000)) MBps" >> $TESTOPFILE
echo "Histogram Scale factor:$scale" >> $TESTOPFILE
echo " " >> $TESTOPFILE

low=0
high=$bucketSize

: > $TMPRANGEOPFILE

while [ $low -lt $rangeMax ]
do
	count=0
	while read p; do
		if [ "$p" -gt "$low" ] && [ "$p" -le "$high" ]
		then
			count=$((count+=1))
		fi
	done < $TMPSORTEDFILE
	echo "$count" >> $TMPRANGEOPFILE

	low=$((low+=bucketSize))
	high=$((high+=bucketSize))
done

maxhist=`sort -n $TMPRANGEOPFILE | tail -1`
factor=$((maxhist/40))
if [ "$factor" -eq 0 ]
then
	factor=1
fi

bucketSizePerc=$((100/$BUCKETS))

low=0
high=$bucketSizePerc
avgPerc=$((avg*100))
avgPerc=$( ceildiv avgPerc rangeMax )

echo "   %age Max" >> $TESTOPFILE
echo "  ==========" >> $TESTOPFILE
while read p; do
	if [ "$avgPerc" -gt "$low" ] && [ "$avgPerc" -le "$high" ]
	then
		echo -n "->" >> $TESTOPFILE 
	else
		echo -n "  " >> $TESTOPFILE 
	fi

	printf "%3s - %3s : " $((low)) $((high)) >> $TESTOPFILE 
	#echo -n "$low        :"
	chars=$((p/factor))
	chars=$((chars*scale))
	if [ "$chars" -eq 0 ] && [ "$p" -ne 0 ]
	then
		chars=1
	fi
	count=1
	while [ $count -le $chars ]
	do
		echo -n "=" >> $TESTOPFILE
		count=$((count+1))
	done
	echo " " >> $TESTOPFILE 

	low=$((low+=bucketSizePerc))
	high=$((high+=bucketSizePerc))
done < $TMPRANGEOPFILE

echo " " >> $TESTOPFILE 
grep "Executed " $TESTSTATFILES >> $TESTOPFILE

rm $TMPSORTEDFILE
rm $TMPRANGEOPFILE
rm $TMPSTATFILE

cat $TESTOPFILE


