##################################################################
#
# Foreman for C++
#
# Copyright (C) Satoshi Konno 2017
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

TESTS = foremantest
noinst_PROGRAMS = foremantest

AM_CPPFLAGS = -I$(top_srcdir)/include -I../

foremantest_SOURCES = \
	../MetricsTests.cpp \
	../MemStoreTests.cpp \
	../ForemanTest.cpp \
	../MemStoreTestController.cpp \
	../TimeSeriesTests.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
