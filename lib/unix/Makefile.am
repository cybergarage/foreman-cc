##################################################################
#
# Foreman for C++
#
# Copyright (C) Satoshi Konno 2017
#
# This is licensed under BSD-style license, see file COPYING.
#
##################################################################

lib_LIBRARIES = libforeman++.a

AM_CPPFLAGS = -I$(top_srcdir)/include

foremancc_sources = \
	../../src/beringei/BitUtil.cpp \
	../../src/beringei/TimeSeriesStream.cpp \
	../../src/foreman/ArrayTimeSeries.cpp \
	../../src/foreman/BeringeiTimeSeries.cpp \
	../../src/foreman/GraphiteStore.cpp \
	../../src/foreman/MatrixStore.cpp \
	../../src/foreman/MemStore.cpp \
	../../src/foreman/Metric.cpp \
	../../src/foreman/MetricMap.cpp \
	../../src/foreman/NarrowTableStore.cpp \
	../../src/foreman/net/Graphite.cpp \
	../../src/foreman/net/HttpClient.cpp \
	../../src/foreman/net/Socket.cpp \
	../../src/foreman/RingArrayTimeSeries.cpp \
	../../src/foreman/RingMapStore.cpp \
	../../src/foreman/SQLiteStore.cpp \
	../../src/foreman/StaticArrayTimeSeries.cpp \
	../../src/foreman/Store.cpp \
	../../src/foreman/TimeSeries.cpp \
	../../src/foreman/TimeSeriesMap.cpp \
	../../src/foreman/TimeSeriesMapStore.cpp \
	../../src/foreman/TSmapStore.cpp

libforeman___a_SOURCES = \
        $(foremancc_sources)
