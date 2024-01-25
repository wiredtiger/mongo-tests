#!/bin/bash
set -uexo pipefail
cd wiredtiger/build/examples/c
for f in ex_*; do
    if [[ "$f" != ex_tiered ]]; then
        ls -l "$f/$f"
        "$f/$f"
    fi
done
rm -rf WT_* backup_*
