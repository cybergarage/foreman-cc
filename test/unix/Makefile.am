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
	..//util/MutexTest.cpp \
	..//util/UUIDTest.cpp \
	..//binding/clang/common/ClangErrorTest.cpp \
	..//binding/clang/action/ClangScriptManagerTest.cpp \
	..//binding/clang/action/ClangParameterTest.cpp \
	..//binding/clang/action/ClangMethodTest.cpp \
	..//binding/clang/register/ClangStoreTest.cpp \
	..//binding/clang/register/ClangObjectTest.cpp \
	..//binding/clang/registry/ClangStoreTest.cpp \
	..//binding/clang/registry/ClangQueryTest.cpp \
	..//binding/clang/registry/ClangObjectTest.cpp \
	..//binding/clang/registry/ClangPropertyTest.cpp \
	..//binding/clang/metric/ClangMetricStoreTest.cpp \
	..//binding/clang/metric/ClangQueryTest.cpp \
	..//binding/clang/metric/ClangResultSetTest.cpp \
	..//binding/clang/metric/ClangMetricsTest.cpp \
	..//common/ErrorTest.cpp \
	..//action/PythonEngineTest.cpp \
	..//action/ParameterTest.cpp \
	..//action/LuaEngineTest.cpp \
	..//action/MethodTest.cpp \
	..//action/ManagerTestController.cpp \
	..//action/SystemEngineTest.cpp \
	..//register/ObjectTest.cpp \
	..//register/StoreTestController.cpp \
	..//register/StoreTest.cpp \
	..//ForemanTest.cpp \
	..//registry/ObjectTest.cpp \
	..//registry/PropertyTest.cpp \
	..//registry/StoreTestController.cpp \
	..//registry/StoreTest.cpp \
	..//registry/QueryTest.cpp \
	..//metric/MetricsTest.cpp \
	..//metric/TimeSeriesTest.cpp \
	..//metric/StoreTestController.cpp \
	..//metric/DataPointTest.cpp \
	..//metric/StoreTest.cpp \
	..//metric/MetricTest.cpp \
	..//metric/QueryTest.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
