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
	..//clang/ClangMetricsTests.cpp \
	..//clang/ClangQueryTests.cpp \
	..//clang/ClangResultSetTests.cpp \
	..//clang/ClangStoreTest.cpp \
	..//ForemanTest.cpp \
	..//MemStoreTestController.cpp \
	..//MemStoreTests.cpp \
	..//MetricsTests.cpp \
	..//QueryTest.cpp \
	..//TimeSeriesTests.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
