#!/bin/bash
set -uexo pipefail
cd wiredtiger/build
test/packing/packing-direct-test-all
rm -rf WT_TEST
