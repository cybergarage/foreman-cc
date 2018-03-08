#! /bin/bash

set -xue
shopt -s extglob

# generate aclocal.m4
aclocal
# update all the timestamps so that make doesn't try to call autotools
touch configure.ac aclocal.m4 configure Makefile.am **/Makefile.{in,am} config.h.in config/*
