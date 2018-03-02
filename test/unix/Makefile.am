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
	../binding/clang/register/ClangStoreTest.cpp \
	../binding/clang/register/ClangObjectTest.cpp \
	../binding/clang/common/ClangErrorTest.cpp \
	../binding/clang/action/ClangScriptManagerTest.cpp \
	../binding/clang/action/ClangParameterTest.cpp \
	../binding/clang/action/ClangMethodTest.cpp \
	../binding/clang/metric/ClangQueryTest.cpp \
	../binding/clang/metric/ClangMetricsTest.cpp \
	../binding/clang/metric/ClangResultSetTest.cpp \
	../binding/clang/metric/ClangStoreTest.cpp \
	../binding/clang/registry/ClangQueryTest.cpp \
	../binding/clang/registry/ClangPropertyTest.cpp \
	../binding/clang/registry/ClangStoreTest.cpp \
	../binding/clang/registry/ClangObjectTest.cpp \
	../register/StoreTest.cpp \
	../register/StoreTestController.cpp \
	../register/ObjectTest.cpp \
	../common/ErrorTest.cpp \
	../util/UUIDTest.cpp \
	../util/MutexTest.cpp \
	../action/ManagerTest.cpp \
	../action/LuaEngineTest.cpp \
	../action/ParameterTest.cpp \
	../action/MethodTest.cpp \
	../action/PythonEngineTest.cpp \
	../action/ManagerTestController.cpp \
	../metric/MetricsTest.cpp \
	../metric/MetricTest.cpp \
	../metric/TimeSeriesTest.cpp \
	../metric/StoreTest.cpp \
	../metric/DataPointTest.cpp \
	../metric/StoreTestController.cpp \
	../metric/QueryTest.cpp \
	../registry/PropertyTest.cpp \
	../registry/StoreTest.cpp \
	../registry/StoreTestController.cpp \
	../registry/QueryTest.cpp \
	../registry/ObjectTest.cpp \
	../ForemanTest.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
