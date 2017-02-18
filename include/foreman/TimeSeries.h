/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_TIMESERIES_H_
#define _FOREMANCC_TIMESERIES_H_

#include <string>
#include <unordered_map>

#include <foreman/Metric.h>

namespace Foreman {

////////////////////////////////////////////////
// TimeSeries
////////////////////////////////////////////////

class TimeSeries {
  public:
  TimeSeries();
  virtual ~TimeSeries();

  virtual bool getData(size_t offset, size_t length, std::shared_ptr<MetricData>& data) = 0;
  virtual size_t getDataSize() = 0;

  std::string name;
  
  time_t firstTimestamp;
  time_t lastTimestamp;
};

////////////////////////////////////////////////
// TimeSeriesMap
////////////////////////////////////////////////

typedef std::pair<std::string, std::shared_ptr<TimeSeries>> TimeSeriesPair;

class TimeSeriesMap : public std::unordered_map<std::string, std::shared_ptr<TimeSeries>> {
  public:
  TimeSeriesMap();
  virtual ~TimeSeriesMap();
};

////////////////////////////////////////////////
// ArrayTimeSeries
////////////////////////////////////////////////

class ArrayTimeSeries : public TimeSeries {
public:
  ArrayTimeSeries();
  ~ArrayTimeSeries();
  bool getData(size_t offset, size_t length, std::shared_ptr<MetricData>& data);
  size_t getDataSize();
  MetricData* row;
  size_t rowSize;
};

////////////////////////////////////////////////
// ArrayTimeSeriesMap
////////////////////////////////////////////////

class ArrayTimeSeriesMap : public TimeSeriesMap {
public:
  ArrayTimeSeriesMap() {}
  ~ArrayTimeSeriesMap() {}
  std::shared_ptr<MetricData> data;
};

}

#endif
