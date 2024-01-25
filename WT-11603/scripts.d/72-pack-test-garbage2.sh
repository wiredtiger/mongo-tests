#!/bin/bash
set -u
cd wiredtiger/build || exit $?
optypes=`test/packing/packing-direct-test-unpack | egrep '^  '`

columns() {
    perl -E '
        @f1 = ($ARGV[0] =~ /.+/g); # split /\n/, $ARGV[0];
        @f2 = ($ARGV[1] =~ /.+/g); # split /\n/, $ARGV[1];
        my $nLines = $#f1 > $#f2 ? $#f1 : $#f2;
        my $W = 160;
        my $W1 = int(($W-3)/2);
        for my $l (0 .. $nLines) {
            my @ll = ($f1[$l], $f2[$l]);
            my $nl = 0;
            for (@ll) {
                my $n1 = int((length($_) + $W1 - 1) / $W1) - 1;
                $nl = $n1 if $n1 > $nl;
            }
            my $sep = ($ll[0] eq $ll[1]) ? "   " : " ! ";
            for my $part (0 .. $nl) {
                say join $sep, map {sprintf "%-${W1}s", substr $_, $W1*$part, $W1} @ll;
            }
        }
    ' "$@"
}

testop() {
    local FMT="$(test/packing/packing-direct-test-unpack garbage $1    fmt $2 2>&1 | perl -npE 's/^\[.*?, /  ERROR: / && s/, \d+: /: / && s/(direct|fmt)[\w\-]*/\@/g')"
    local DIR="$(test/packing/packing-direct-test-unpack garbage $1 direct $2 2>&1 | perl -npE 's/^\[.*?, /  ERROR: / && s/, \d+: /: / && s/(direct|fmt)[\w\-]*/\@/g')"
    [[ "$FMT" == "$DIR" ]] || echo "        >>>>>>> $1 $2"$'\n==== FMT:\n'"$FMT"$'\n==== DIRECT:\n'"$DIR"
}
testn() {
    echo -n $1$'\r' 1>&2
    #for op in $optypes; do testop $1 $op; done
    local FMT="$(test/packing/packing-direct-test-unpack garbage $1    fmt $optypes 2>&1 | perl -npE 's/^\[.*?, /  ERROR: / && s/, \d+: /: / && s/(direct|fmt)[\w\-]*/\@/g')"
    local DIR="$(test/packing/packing-direct-test-unpack garbage $1 direct $optypes 2>&1 | perl -npE 's/^\[.*?, /  ERROR: / && s/, \d+: /: / && s/(direct|fmt)[\w\-]*/\@/g')"
    [[ "$FMT" == "$DIR" ]] || echo ">>>>>>> $1"$'\n==== '"$1"$' FMT:\n'"$FMT"$'\n==== '"$1"$' DIRECT:\n'"$DIR"
}
testp() {
    local FMT="$(../test/packing/packing-direct-test-unpack garbage $1    fmt $optypes 2>&1 | perl -npE 's/^\[.*?, /  ERROR: / && s/, \d+: /: / && s/(direct|fmt)[\w\-]*/\@/g')"
    local DIR="$(../test/packing/packing-direct-test-unpack garbage $1 direct $optypes 2>&1 | perl -npE 's/^\[.*?, /  ERROR: / && s/, \d+: /: / && s/(direct|fmt)[\w\-]*/\@/g')"
    #[[ "$FMT" == "$DIR" ]] || echo "******** $1"$'\n==== '"$1"$' FMT:\n'"$FMT"$'\n==== '"$1"$' DIRECT:\n'"$DIR"
    #[[ "$FMT" == "$DIR" ]] || { echo "diff FMT-$1 DIRECT-$1"; diff -ab -L FMT -L DIRECT <(echo "$FMT") <(echo "$DIR"); }
    [[ "$FMT" == "$DIR" ]] || { echo "******** $1      FMT  |  DIRECT"; columns "$FMT" "$DIR"; }
}

#for i in `seq 0 999`; do testn $i; done
#rm -rf WT_TEST

rm -f garbage-diff
mkdir -p `seq 0 9`
for i in `seq 0 99`; do
    echo -n $i$'\r' 1>&2
    for j in `seq 0 9`; do
        ( cd $j; testp $i$j > out.txt; ) &
    done
    wait
    cat `seq -s '/out.txt ' 0 9` >> garbage-diff
done
rm -rf WT_TEST `seq 0 9`

cd ../..
diff -q packing-direct-test-garbage2.diff wiredtiger/build/garbage-diff
