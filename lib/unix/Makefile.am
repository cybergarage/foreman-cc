##################################################################
#
# Foreman for C++
#
# Copyright (C) 2017 Satoshi Konno
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

lib_LIBRARIES = libforeman++.a

AM_CPPFLAGS = -I$(top_srcdir)/include

foremancc_sources = \
	../../src/beringei/BitUtil.cpp \
	../../src/beringei/TimeSeriesStream.cpp \
	../../src/foreman/action/impl/DefaultScriptManager.cpp \
	../../src/foreman/action/impl/GlobalObject.cpp \
	../../src/foreman/action/impl/LuaEngine.cpp \
	../../src/foreman/action/impl/PythonEngine.cpp \
	../../src/foreman/action/impl/PythonFunctions.cpp \
	../../src/foreman/action/impl/PythonParameter.cpp \
	../../src/foreman/action/impl/PythonParameters.cpp \
	../../src/foreman/action/impl/PythonScript.cpp \
	../../src/foreman/action/Method.cpp \
	../../src/foreman/action/MethodMap.cpp \
	../../src/foreman/action/Parameter.cpp \
	../../src/foreman/action/Parameters.cpp \
	../../src/foreman/action/ScriptEngine.cpp \
	../../src/foreman/action/ScriptEngineMap.cpp \
	../../src/foreman/action/ScriptManager.cpp \
	../../src/foreman/binding/clang/action/method_c.cpp \
	../../src/foreman/binding/clang/action/parameter_c.cpp \
	../../src/foreman/binding/clang/action/parameters_c.cpp \
	../../src/foreman/binding/clang/action/script_manager_c.cpp \
	../../src/foreman/binding/clang/common/error_c.cpp \
	../../src/foreman/binding/clang/metric/datapoint_c.cpp \
	../../src/foreman/binding/clang/metric/datapoints_c.cpp \
	../../src/foreman/binding/clang/metric/metric_c.cpp \
	../../src/foreman/binding/clang/metric/query_c.cpp \
	../../src/foreman/binding/clang/metric/resultset_c.cpp \
	../../src/foreman/binding/clang/metric/store_c.cpp \
	../../src/foreman/binding/clang/metric/store_c_factory.cpp \
	../../src/foreman/binding/clang/register/object_c.cpp \
	../../src/foreman/binding/clang/register/store_c.cpp \
	../../src/foreman/binding/clang/registry/object_c.cpp \
	../../src/foreman/binding/clang/registry/objects_c.cpp \
	../../src/foreman/binding/clang/registry/properties_c.cpp \
	../../src/foreman/binding/clang/registry/property_c.cpp \
	../../src/foreman/binding/clang/registry/query_c.cpp \
	../../src/foreman/binding/clang/registry/store_c.cpp \
	../../src/foreman/common/Error.cpp \
	../../src/foreman/metric/Data.cpp \
	../../src/foreman/metric/DataMap.cpp \
	../../src/foreman/metric/DataPoint.cpp \
	../../src/foreman/metric/DataPoints.cpp \
	../../src/foreman/metric/DataPointsMap.cpp \
	../../src/foreman/metric/impl/ArrayTimeSeries.cpp \
	../../src/foreman/metric/impl/BeringeiTimeSeries.cpp \
	../../src/foreman/metric/impl/GraphiteStore.cpp \
	../../src/foreman/metric/impl/MatrixStore.cpp \
	../../src/foreman/metric/impl/MemStore.cpp \
	../../src/foreman/metric/impl/NarrowTableStore.cpp \
	../../src/foreman/metric/impl/RingArrayTimeSeries.cpp \
	../../src/foreman/metric/impl/RingMapStore.cpp \
	../../src/foreman/metric/impl/SQLiteStore.cpp \
	../../src/foreman/metric/impl/StaticArrayTimeSeries.cpp \
	../../src/foreman/metric/impl/TimeSeries.cpp \
	../../src/foreman/metric/impl/TimeSeriesMap.cpp \
	../../src/foreman/metric/impl/TimeSeriesMapStore.cpp \
	../../src/foreman/metric/impl/TSmapStore.cpp \
	../../src/foreman/metric/Query.cpp \
	../../src/foreman/metric/ResultSet.cpp \
	../../src/foreman/metric/Store.cpp \
	../../src/foreman/net/Graphite.cpp \
	../../src/foreman/net/HttpClient.cpp \
	../../src/foreman/register/impl/MemStore.cpp \
	../../src/foreman/register/impl/ObjectMap.cpp \
	../../src/foreman/register/Object.cpp \
	../../src/foreman/register/Store.cpp \
	../../src/foreman/registry/impl/SQLiteStore.cpp \
	../../src/foreman/registry/impl/SQLStore.cpp \
	../../src/foreman/registry/Object.cpp \
	../../src/foreman/registry/Objects.cpp \
	../../src/foreman/registry/Properties.cpp \
	../../src/foreman/registry/Property.cpp \
	../../src/foreman/registry/Query.cpp \
	../../src/foreman/registry/Store.cpp \
	../../src/foreman/util/Mutex.cpp \
	../../src/foreman/util/Util.cpp \
	../../src/foreman/util/UUID.cpp

libforeman___a_SOURCES = \
        $(foremancc_sources)
