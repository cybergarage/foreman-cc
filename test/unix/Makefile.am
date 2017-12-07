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
	..//action/LuaEngineTest.cpp \
	..//action/MethodTest.cpp \
	..//action/ParameterTest.cpp \
	..//action/PythonEngineTest.cpp \
	..//action/ScriptManagerTestController.cpp \
	..//clang/action/ClangMethodTest.cpp \
	..//clang/action/ClangParameterTest.cpp \
	..//clang/action/ClangScriptManagerTest.cpp \
	..//clang/common/ClangErrorTest.cpp \
	..//clang/metric/ClangMetricsTest.cpp \
	..//clang/metric/ClangQueryTest.cpp \
	..//clang/metric/ClangResultSetTest.cpp \
	..//clang/metric/ClangStoreTest.cpp \
	..//clang/registry/ClangObjectTest.cpp \
	..//clang/registry/ClangPropertyTest.cpp \
	..//clang/registry/ClangQueryTest.cpp \
	..//clang/registry/ClangStoreTest.cpp \
	..//common/ErrorTest.cpp \
	..//ForemanTest.cpp \
	..//metric/DataPointTest.cpp \
	..//metric/MetricsTest.cpp \
	..//metric/QueryTest.cpp \
	..//metric/StoreTest.cpp \
	..//metric/StoreTestController.cpp \
	..//metric/TimeSeriesTest.cpp \
	..//registry/ObjectTest.cpp \
	..//registry/PropertyTest.cpp \
	..//registry/QueryTest.cpp \
	..//registry/StoreTest.cpp \
	..//registry/StoreTestController.cpp \
	..//util/MutexTest.cpp \
	..//util/UUIDTest.cpp

foremantest_LDADD = ../../lib/unix/libforeman++.a
