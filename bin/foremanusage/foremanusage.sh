#!/bin/bash
foremanusage=unix/foremanusage

memStores=(matrix ringmap narrowtable tsmap)
retentionPeriods=(1 4 8 16 32)
repetationCnt=1

if [ $# -ge 1 ]; then
  repetationCnt=$1
fi

for m in ${memStores[@]}; do
  for p in ${retentionPeriods[@]}; do
    n=$repetationCnt
    while [ $n -gt 0 ]; do
      ${foremanusage} $m $p
      n=$((n-1))
    done
  done
done
