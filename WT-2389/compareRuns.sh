#!/bin/sh
# Usage: sh compareRuns.sh <baseline-report> <latest-report> <optional-separation-width>

if [ $# -lt 2 ] || [ $# -gt 3 ]; then
	echo "Usage: sh compareRuns.sh <baseline-report> <latest-report> <optional-separation-width>"
	exit 1
fi

sepwidth=120

if [ $# -eq 3 ]; then
	sepwidth=$3
fi

pr -m -t $1 $2 -w $sepwidth

