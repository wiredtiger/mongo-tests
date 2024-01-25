#!/bin/bash
set -uexo pipefail
mkdir -p wiredtiger/build
cd wiredtiger/build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G Ninja ..
