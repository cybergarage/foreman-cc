##################################################################
#
# Foreman for C++
#
# Copyright (C) 2017 Satoshi Konno
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

bin_PROGRAMS = foremanusage

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src -I../ -I../../foremanbench

foremanusage_SOURCES = \
	../foremanusage.cpp \
	../../foremanbench/BenchmarkController.cpp

foremanusage_LDADD = ../../../lib/unix/libforeman++.a
