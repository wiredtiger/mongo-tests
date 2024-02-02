#!/bin/bash
set -uexo pipefail
cd wiredtiger
test/packing/log_auto-mirror-gen.sh
