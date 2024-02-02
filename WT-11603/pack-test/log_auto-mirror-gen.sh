#!/bin/bash

GITHOME="$(git rev-parse --show-toplevel)"
cd "$GITHOME/dist"

FILE=src/include/extern.h
git show HEAD:$FILE > "$GITHOME/$FILE"
python3 < "$GITHOME/test/packing/log_auto-test-mirrordefs-gen.py" >> "$GITHOME/$FILE"

FILE=src/include/intpack_inline.h
echo "#pragma once" > "$GITHOME/$FILE"
git show HEAD:$FILE >> "$GITHOME/$FILE"

FILE=src/log/log_auto.c
echo "#define LOG_AUTO_C" > "$GITHOME/$FILE"
git show HEAD:$FILE >> "$GITHOME/$FILE"

FILE=test/utility/test_util.h
git show HEAD:$FILE | perl -npE 's{\Q#include "wt_internal.h"}{#include "../../src/include/wt_internal.h"}' > "$GITHOME/$FILE"
