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
	..//clang/common/ClangErrorTest.cpp \
	..//clang/action/ClangScriptManagerTest.cpp \
	..//clang/action/ClangParameterTest.cpp \
	..//clang/action/ClangMethodTest.cpp \
	..//clang/registry/ClangStoreTest.cpp \
	..//clang/registry/ClangQueryTest.cpp \
	..//clang/registry/ClangObjectTest.cpp \
	..//clang/registry/ClangPropertyTest.cpp \
	..//clang/metric/ClangStoreTest.cpp \
	..//clang/metric/ClangQueryTest.cpp \
	..//clang/metric/ClangResultSetTest.cpp \
	..//clang/metric/ClangMetricsTest.cpp \
	..//util/MutexTest.cpp \
	..//util/UUIDTest.cpp \
	..//common/ErrorTest.cpp \
	..//action/ScriptManagerTestController.cpp \
	..//action/PythonEngineTest.cpp \
	..//action/ParameterTest.cpp \
	..//action/LuaEngineTest.cpp \
	..//action/MethodTest.cpp \
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
	..//metric/QueryTest.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
