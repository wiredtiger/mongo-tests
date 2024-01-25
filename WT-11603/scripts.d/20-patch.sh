#!/bin/bash
set -uexo pipefail
cd wiredtiger/test/packing
cp -a ../../../pack-test/* ./
git co develop -- CMakeLists.txt
cat CMakeLists-add >> CMakeLists.txt
rm CMakeLists-add
./log_auto-test-gen.sh
