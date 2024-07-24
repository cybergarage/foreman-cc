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
	../register/StoreTest.cpp \
	../register/ObjectTest.cpp \
	../register/StoreTestController.cpp \
	../action/MethodTest.cpp \
	../action/ManagerTestController.cpp \
	../action/ParameterTest.cpp \
	../action/UnknownEngineTest.cpp \
	../action/SystemEngineTest.cpp \
	../action/PythonEngineTest.cpp \
	../action/LuaEngineTest.cpp \
	../registry/PropertyTest.cpp \
	../registry/StoreTest.cpp \
	../registry/ObjectTest.cpp \
	../registry/QueryTest.cpp \
	../registry/StoreTestController.cpp \
	../ClientTest.cpp \
	../log/LoggerTest.cpp \
	../log/LoggerTestController.cpp \
	../binding/clang/register/ClangStoreTest.cpp \
	../binding/clang/register/ClangObjectTest.cpp \
	../binding/clang/action/ClangMethodTest.cpp \
	../binding/clang/action/ClangParameterTest.cpp \
	../binding/clang/action/ClangScriptManagerTest.cpp \
	../binding/clang/registry/ClangPropertyTest.cpp \
	../binding/clang/registry/ClangStoreTest.cpp \
	../binding/clang/registry/ClangObjectTest.cpp \
	../binding/clang/registry/ClangQueryTest.cpp \
	../binding/clang/log/ClangLoggerTest.cpp \
	../binding/clang/metric/ClangMetricsTest.cpp \
	../binding/clang/metric/ClangMetricStoreTest.cpp \
	../binding/clang/metric/ClangResultSetTest.cpp \
	../binding/clang/metric/ClangQueryTest.cpp \
	../binding/clang/common/ClangErrorTest.cpp \
	../metric/DataPointTest.cpp \
	../metric/MetricsTest.cpp \
	../metric/TimeSeriesTest.cpp \
	../metric/StoreTest.cpp \
	../metric/MetricTest.cpp \
	../metric/QueryTest.cpp \
	../metric/StoreTestController.cpp \
	../util/UUIDTest.cpp \
	../util/MutexTest.cpp \
	../ForemanTest.cpp \
	../common/ErrorTest.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
