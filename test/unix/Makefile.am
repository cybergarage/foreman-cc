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
	../log/LoggerTestController.cpp \
	../log/LoggerTest.cpp \
	../binding/clang/log/ClangLoggerTest.cpp \
	../binding/clang/common/ClangErrorTest.cpp \
	../binding/clang/action/ClangParameterTest.cpp \
	../binding/clang/action/ClangMethodTest.cpp \
	../binding/clang/action/ClangScriptManagerTest.cpp \
	../binding/clang/registry/ClangQueryTest.cpp \
	../binding/clang/registry/ClangPropertyTest.cpp \
	../binding/clang/registry/ClangObjectTest.cpp \
	../binding/clang/registry/ClangStoreTest.cpp \
	../binding/clang/register/ClangObjectTest.cpp \
	../binding/clang/register/ClangStoreTest.cpp \
	../binding/clang/metric/ClangQueryTest.cpp \
	../binding/clang/metric/ClangMetricStoreTest.cpp \
	../binding/clang/metric/ClangResultSetTest.cpp \
	../binding/clang/metric/ClangMetricsTest.cpp \
	../common/ErrorTest.cpp \
	../action/MethodTest.cpp \
	../action/SystemEngineTest.cpp \
	../action/UnknownEngineTest.cpp \
	../action/LuaEngineTest.cpp \
	../action/ParameterTest.cpp \
	../action/ManagerTestController.cpp \
	../action/PythonEngineTest.cpp \
	../registry/PropertyTest.cpp \
	../registry/QueryTest.cpp \
	../registry/StoreTestController.cpp \
	../registry/ObjectTest.cpp \
	../registry/StoreTest.cpp \
	../ClientTest.cpp \
	../util/UUIDTest.cpp \
	../util/MutexTest.cpp \
	../ForemanTest.cpp \
	../register/StoreTestController.cpp \
	../register/ObjectTest.cpp \
	../register/StoreTest.cpp \
	../metric/DataPointTest.cpp \
	../metric/QueryTest.cpp \
	../metric/TimeSeriesTest.cpp \
	../metric/MetricsTest.cpp \
	../metric/MetricTest.cpp \
	../metric/StoreTestController.cpp \
	../metric/StoreTest.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
