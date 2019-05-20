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
	../register/ObjectTest.cpp \
	../register/StoreTest.cpp \
	../register/StoreTestController.cpp \
	../metric/DataPointTest.cpp \
	../metric/MetricsTest.cpp \
	../metric/QueryTest.cpp \
	../metric/StoreTest.cpp \
	../metric/MetricTest.cpp \
	../metric/TimeSeriesTest.cpp \
	../metric/StoreTestController.cpp \
	../binding/clang/register/ClangStoreTest.cpp \
	../binding/clang/register/ClangObjectTest.cpp \
	../binding/clang/metric/ClangMetricStoreTest.cpp \
	../binding/clang/metric/ClangMetricsTest.cpp \
	../binding/clang/metric/ClangQueryTest.cpp \
	../binding/clang/metric/ClangResultSetTest.cpp \
	../binding/clang/log/ClangLoggerTest.cpp \
	../binding/clang/common/ClangErrorTest.cpp \
	../binding/clang/action/ClangScriptManagerTest.cpp \
	../binding/clang/action/ClangParameterTest.cpp \
	../binding/clang/action/ClangMethodTest.cpp \
	../binding/clang/registry/ClangPropertyTest.cpp \
	../binding/clang/registry/ClangStoreTest.cpp \
	../binding/clang/registry/ClangQueryTest.cpp \
	../binding/clang/registry/ClangObjectTest.cpp \
	../log/LoggerTest.cpp \
	../log/LoggerTestController.cpp \
	../common/ErrorTest.cpp \
	../action/UnknownEngineTest.cpp \
	../action/SystemEngineTest.cpp \
	../action/PythonEngineTest.cpp \
	../action/ParameterTest.cpp \
	../action/LuaEngineTest.cpp \
	../action/ManagerTestController.cpp \
	../action/MethodTest.cpp \
	../ClientTest.cpp \
	../registry/PropertyTest.cpp \
	../registry/QueryTest.cpp \
	../registry/ObjectTest.cpp \
	../registry/StoreTest.cpp \
	../registry/StoreTestController.cpp \
	../util/MutexTest.cpp \
	../util/UUIDTest.cpp \
	../ForemanTest.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
