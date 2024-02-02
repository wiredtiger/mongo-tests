#!/bin/bash
set -uexo pipefail
[[ -d wiredtiger ]] && exit
git clone https://github.com/wiredtiger/wiredtiger.git # git@github.com:wiredtiger/wiredtiger
