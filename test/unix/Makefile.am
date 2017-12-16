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
	../util/MutexTest.cpp \
	../util/UUIDTest.cpp \
	../action/PythonEngineTest.cpp \
	../action/ParameterTest.cpp \
	../action/MethodTest.cpp \
	../action/ScriptManagerTestController.cpp \
	../action/LuaEngineTest.cpp \
	../ForemanTest.cpp \
	../clang/action/ClangMethodTest.cpp \
	../clang/action/ClangScriptManagerTest.cpp \
	../clang/action/ClangParameterTest.cpp \
	../clang/registry/ClangStoreTest.cpp \
	../clang/registry/ClangQueryTest.cpp \
	../clang/registry/ClangObjectTest.cpp \
	../clang/registry/ClangPropertyTest.cpp \
	../clang/metric/ClangStoreTest.cpp \
	../clang/metric/ClangQueryTest.cpp \
	../clang/metric/ClangResultSetTest.cpp \
	../clang/metric/ClangMetricsTest.cpp \
	../clang/common/ClangErrorTest.cpp \
	../registry/QueryTest.cpp \
	../registry/ObjectTest.cpp \
	../registry/StoreTest.cpp \
	../registry/StoreTestController.cpp \
	../registry/PropertyTest.cpp \
	../metric/DataPointTest.cpp \
	../metric/QueryTest.cpp \
	../metric/TimeSeriesTest.cpp \
	../metric/MetricsTest.cpp \
	../metric/StoreTest.cpp \
	../metric/StoreTestController.cpp \
	../common/ErrorTest.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
