export MAX_ROWS=200000000
export LENGTH_CHAR_FIELDS=2000
CWD=`pwd`
cd ~/work/iibench-mongodb/
./run.simple.bash > $CWD/restults.txt
