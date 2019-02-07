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
	../ClientTest.cpp \
	../ForemanTest.cpp \
	../action/LuaEngineTest.cpp \
	../action/ManagerTestController.cpp \
	../action/MethodTest.cpp \
	../action/ParameterTest.cpp \
	../action/PythonEngineTest.cpp \
	../action/SystemEngineTest.cpp \
	../action/UnknownEngineTest.cpp \
	../binding/clang/action/ClangMethodTest.cpp \
	../binding/clang/action/ClangParameterTest.cpp \
	../binding/clang/action/ClangScriptManagerTest.cpp \
	../binding/clang/common/ClangErrorTest.cpp \
	../binding/clang/log/ClangLoggerTest.cpp \
	../binding/clang/metric/ClangMetricStoreTest.cpp \
	../binding/clang/metric/ClangMetricsTest.cpp \
	../binding/clang/metric/ClangQueryTest.cpp \
	../binding/clang/metric/ClangResultSetTest.cpp \
	../binding/clang/register/ClangObjectTest.cpp \
	../binding/clang/register/ClangStoreTest.cpp \
	../binding/clang/registry/ClangObjectTest.cpp \
	../binding/clang/registry/ClangPropertyTest.cpp \
	../binding/clang/registry/ClangQueryTest.cpp \
	../binding/clang/registry/ClangStoreTest.cpp \
	../common/ErrorTest.cpp \
	../log/LoggerTest.cpp \
	../log/LoggerTestController.cpp \
	../metric/DataPointTest.cpp \
	../metric/MetricTest.cpp \
	../metric/MetricsTest.cpp \
	../metric/QueryTest.cpp \
	../metric/StoreTest.cpp \
	../metric/StoreTestController.cpp \
	../metric/TimeSeriesTest.cpp \
	../register/ObjectTest.cpp \
	../register/StoreTest.cpp \
	../register/StoreTestController.cpp \
	../registry/ObjectTest.cpp \
	../registry/PropertyTest.cpp \
	../registry/QueryTest.cpp \
	../registry/StoreTest.cpp \
	../registry/StoreTestController.cpp \
	../util/MutexTest.cpp \
	../util/UUIDTest.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
