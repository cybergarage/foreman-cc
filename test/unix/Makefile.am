##################################################################
#
# Foreman for C++
#
# Copyright (C) 2017 Satoshi Konno
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
	..//DataPointTests.cpp \
	..//ForemanTest.cpp \
	..//MetricsTests.cpp \
	..//QueryTest.cpp \
	..//StoreTestController.cpp \
	..//StoreTests.cpp \
	..//TimeSeriesTests.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
