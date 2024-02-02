#!/bin/bash

GITHOME="$(git rev-parse --show-toplevel)"
cd "$GITHOME/dist"

FILE="src/include/extern.h"
git show HEAD:$FILE > "$GITHOME/$FILE"

FILE=src/include/intpack_inline.h
echo "#pragma once" > "$GITHOME/$FILE"
git show HEAD:$FILE >> "$GITHOME/$FILE"

FILE=src/log/log_auto.c
git show HEAD:$FILE > "$GITHOME/$FILE"

FILE=test/utility/test_util.h
git show HEAD:$FILE > "$GITHOME/$FILE"
