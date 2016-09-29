CWD=`pwd`
cd /data/mytools/bench/run_linkbench
bash all.sh wt.1b.zlib /data/mongo-tests/david-framework/mongo/mongo /data/db 10000001 md2 16 3600 mongo ignore 24 localhost 4 16 24 48 2>&1 > $CWD/results.txt
