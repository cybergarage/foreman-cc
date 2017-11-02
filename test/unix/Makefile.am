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
	..//clang/common/ClangErrorTests.cpp \
	..//clang/metric/ClangMetricsTests.cpp \
	..//clang/metric/ClangQueryTests.cpp \
	..//clang/metric/ClangResultSetTests.cpp \
	..//clang/metric/ClangStoreTest.cpp \
	..//common/ErrorTest.cpp \
	..//ForemanTest.cpp \
	..//metric/DataPointTests.cpp \
	..//metric/MetricsTests.cpp \
	..//metric/QueryTest.cpp \
	..//metric/StoreTestController.cpp \
	..//metric/StoreTests.cpp \
	..//metric/TimeSeriesTests.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
