#!/bin/bash
set -ueo pipefail
cd `dirname -- "${BASH_SOURCE[0]}"`
for f in `ls -1 run.d/*`; do echo "===== $f"; $f; done
