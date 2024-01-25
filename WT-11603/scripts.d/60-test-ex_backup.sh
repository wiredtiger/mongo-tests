#!/bin/bash
set -uexo pipefail
cd wiredtiger/build/examples/c
ex_backup/ex_backup
rm -rf backup_full.1 WT_HOME_LOG*
