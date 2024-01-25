#!/bin/bash
set -u
cd wiredtiger/build || exit $?
#test/packing/packing-direct-test-garbage
test() { $1 2>&1 | perl -npE 's/^\[.*?, /  ERROR: / && s/, \d+: /: / && s/(direct|fmt)[\w\-]*/\@/g' > `basename $1`.txt; ERR="${PIPESTATUS[0]}"; }
test test/packing/packing-direct-test-garbage-fmt                  ; ERR1=$ERR
test test/packing/packing-direct-test-garbage-direct-nocheckcompat ; ERR2=$ERR
echo Exit codes: FMT=$ERR1 DIRECT=$ERR2
diff packing-direct-test-garbage-{fmt,direct-nocheckcompat}.txt > packing-direct-test-garbage.diff
diff -q ../../packing-direct-test-garbage.diff packing-direct-test-garbage.diff || {
    echo Garbage diff mismatch: wiredtiger/build/packing-direct-test-garbage*
    echo '  $ diff wiredtiger/build/packing-direct-test-garbage-{fmt,direct-nocheckcompat}.txt'
    echo ... diff file: wiredtiger/build/packing-direct-test-garbage.diff
    exit 1
}
rm -rf packing-direct-test-garbage-{fmt,direct-nocheckcompat}.txt packing-direct-test-garbage.diff
exit
