#!/bin/bash

set -euo pipefail

GITHOME="$(git rev-parse --show-toplevel)"

cd "$GITHOME/dist"
"$GITHOME/test/packing/log_auto-unmirror-gen.sh"
cd "$GITHOME"

export MYNAME=`basename "$0"`

# 3f576a00af has the latest version of the old generation packing routines.
git show 3f576a00af:src/log/log_auto.c | SUFFIX=fmt    perl "$GITHOME/test/packing/log_auto-src-prepare.pl" > test/packing/log_auto_fmt.h
                cat src/log/log_auto.c | SUFFIX=direct perl "$GITHOME/test/packing/log_auto-src-prepare.pl" > test/packing/log_auto_direct.h

cd "$GITHOME/test/packing/"
./packing-direct-test-gen.py '    test_cmp_all((WT_SESSION_IMPL *)g.wt_session);'            > packing-direct-test-all.c
./packing-direct-test-gen.py '    test_garbage_all((WT_SESSION_IMPL *)g.wt_session);'        > packing-direct-test-garbage.c
./packing-direct-test-gen.py '    test_garbage_all_fmt((WT_SESSION_IMPL *)g.wt_session);'    > packing-direct-test-garbage-fmt.c
./packing-direct-test-gen.py '    test_garbage_all_direct((WT_SESSION_IMPL *)g.wt_session);' > packing-direct-test-garbage-direct.c
echo "#define NO_STRICT_PACKING_CHECK"    > packing-direct-test-garbage-direct-nocheck.c
cat packing-direct-test-garbage-direct.c >> packing-direct-test-garbage-direct-nocheck.c
echo "#define PACKING_COMPATIBILITY_MODE" > packing-direct-test-garbage-direct-compat.c
cat packing-direct-test-garbage-direct.c >> packing-direct-test-garbage-direct-compat.c
echo "#define NO_STRICT_PACKING_CHECK"    > packing-direct-test-garbage-direct-nocheckcompat.c
echo "#define PACKING_COMPATIBILITY_MODE">> packing-direct-test-garbage-direct-nocheckcompat.c
cat packing-direct-test-garbage-direct.c >> packing-direct-test-garbage-direct-nocheckcompat.c
./packing-direct-test-gen.py '
    if (argc > 2 && !strcmp(argv[1], "gen")) {
        uint8_t garbage[MAX_GARBAGE_SIZE];
        size_t garbage_size;
        init_garbage((size_t)atoi(argv[2]), &garbage, &garbage_size, 1);
        write(1, garbage, garbage_size);
    } else if (argc > 4 && !strcmp(argv[1], "garbage")) {
        uint8_t garbage[MAX_GARBAGE_SIZE];
        size_t garbage_size;
        int i;
        init_garbage((size_t)atoi(argv[2]), &garbage, &garbage_size, 0);
        for (i = 4; i < argc; i++) {
            test_unpack_run((WT_SESSION_IMPL *)g.wt_session, argv[3], argv[i], garbage, (size_t)garbage_size);
        }
    } else if (argc > 3 && !strcmp(argv[1], "stdin")) {
        uint8_t garbage[MAX_GARBAGE_SIZE];
        ssize_t garbage_size;
        int i;
        garbage_size = read(0, garbage, MAX_GARBAGE_SIZE);
        if (garbage_size == -1) {
            perror("read stdin");
            exit(1);
        }
        for (i = 2; i < argc; i++) {
            test_unpack_run((WT_SESSION_IMPL *)g.wt_session, argv[1], argv[i], garbage, (size_t)garbage_size);
        }
    } else {
        printf("Usage:\n"
               "%s gen <seed>  - generate garbage from seed to stdout (binary) and stderr (text)\n"
               "%s stdin <mode> <optype ...>  - decode stdin\n"
               "%s garbage <seed> <mode> <optype ...>  - decode garbage from seed\n"
               "\n"
               "mode: fmt | direct | mirror\n"
               "optypes:\n%s", argv[0], argv[0], argv[0], test_list_ops());
    }
' > packing-direct-test-unpack.c

cd "$GITHOME/dist"
python3 < "$GITHOME/test/packing/log_auto-test-gen.py" > "$GITHOME/test/packing/log_auto_test.h"
python3 < "$GITHOME/test/packing/log_auto-test-mirror-gen.py" > "$GITHOME/test/packing/log_auto_mirror.h"

cd "$GITHOME/dist"
./s_clang_format "$GITHOME/test/packing/log_auto_fmt.h"
./s_clang_format "$GITHOME/test/packing/log_auto_direct.h"
./s_clang_format "$GITHOME/test/packing/log_auto_test.h"
./s_clang_format "$GITHOME/test/packing/log_auto_mirror.h"
./s_clang_format "$GITHOME/test/packing/packing-direct-test-all.c"
./s_clang_format "$GITHOME/test/packing/packing-direct-test-garbage.c"
./s_clang_format "$GITHOME/test/packing/packing-direct-test-garbage-fmt.c"
./s_clang_format "$GITHOME/test/packing/packing-direct-test-garbage-direct.c"
./s_clang_format "$GITHOME/test/packing/packing-direct-test-garbage-direct-nocheck.c"
./s_clang_format "$GITHOME/test/packing/packing-direct-test-garbage-direct-compat.c"
./s_clang_format "$GITHOME/test/packing/packing-direct-test-garbage-direct-nocheckcompat.c"
./s_clang_format "$GITHOME/test/packing/packing-direct-test-unpack.c"
