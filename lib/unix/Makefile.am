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
	../../src/foreman/clang/metric/datapoint_c.cpp \
	../../src/foreman/clang/metric/datapoints_c.cpp \
	../../src/foreman/clang/metric/metric_c.cpp \
	../../src/foreman/clang/metric/query_c.cpp \
	../../src/foreman/clang/metric/resultset_c.cpp \
	../../src/foreman/clang/metric/store_c.cpp \
	../../src/foreman/clang/metric/store_c_factory.cpp \
	../../src/foreman/metric/ArrayTimeSeries.cpp \
	../../src/foreman/metric/BeringeiTimeSeries.cpp \
	../../src/foreman/metric/Data.cpp \
	../../src/foreman/metric/DataMap.cpp \
	../../src/foreman/metric/DataPoint.cpp \
	../../src/foreman/metric/DataPoints.cpp \
	../../src/foreman/metric/DataPointsMap.cpp \
	../../src/foreman/metric/GraphiteStore.cpp \
	../../src/foreman/metric/MatrixStore.cpp \
	../../src/foreman/metric/MemStore.cpp \
	../../src/foreman/metric/NarrowTableStore.cpp \
	../../src/foreman/metric/Query.cpp \
	../../src/foreman/metric/ResultSet.cpp \
	../../src/foreman/metric/RingArrayTimeSeries.cpp \
	../../src/foreman/metric/RingMapStore.cpp \
	../../src/foreman/metric/SQLiteStore.cpp \
	../../src/foreman/metric/StaticArrayTimeSeries.cpp \
	../../src/foreman/metric/Store.cpp \
	../../src/foreman/metric/TimeSeries.cpp \
	../../src/foreman/metric/TimeSeriesMap.cpp \
	../../src/foreman/metric/TimeSeriesMapStore.cpp \
	../../src/foreman/metric/TSmapStore.cpp \
	../../src/foreman/net/Graphite.cpp \
	../../src/foreman/net/HttpClient.cpp \
	../../src/foreman/net/Socket.cpp \
	../../src/foreman/util/Util.cpp

libforeman___a_SOURCES = \
        $(foremancc_sources)
