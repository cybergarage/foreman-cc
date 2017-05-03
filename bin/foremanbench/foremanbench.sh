#!/bin/sh
unix/foremanbench --benchmark_repetitions=10 | awk '{print $1 "," $4;}'
