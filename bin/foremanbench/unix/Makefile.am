##################################################################
#
# Foreman for C++
#
# Copyright (C) Satoshi Konno 2017
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

bin_PROGRAMS = foremanbench

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I../
	..//BenchmarkController.h

foremanbench_SOURCES = \
	..//BenchmarkController.cpp \
	..//foremanbench.cpp

foremanbench_LDADD = ../../../lib/unix/libforeman++.a
