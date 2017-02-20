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

  virtual bool addValue(const Metric& m) = 0;
  virtual bool getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t &valueCnt) = 0;
};

////////////////////////////////////////////////
// TimeSeriesMap
////////////////////////////////////////////////

typedef std::pair<std::string, std::shared_ptr<TimeSeries>> TimeSeriesPair;

class TimeSeriesMap : public std::unordered_map<std::string, std::shared_ptr<TimeSeries>> {
  public:
  TimeSeriesMap();
  virtual ~TimeSeriesMap();

  std::shared_ptr<TimeSeries> find(const Metric& m);

  bool addValue(const Metric& m);
  bool addValues(std::vector<std::shared_ptr<Metric>> metrics);
  bool getValues(const Metric& m, time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t &valueCnt);
};

////////////////////////////////////////////////
// ArrayTimeSeries
////////////////////////////////////////////////

class ArrayTimeSeries : public TimeSeries {
  public:
  ArrayTimeSeries();
  ~ArrayTimeSeries();

  bool addValue(const Metric& m);
  bool getValues(time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& data, size_t &valueCnt);

  bool reallocValueArray(size_t size);
  bool setValueArray(MetricValue* values, size_t size);
  bool clear();

  private:
  MetricValue* rawValues_;
  std::shared_ptr<MetricValue> values_;

  size_t arraySize_;
  size_t arrayInsertIndex_;
  size_t arrayCount_;

  time_t firstTs_;
  time_t lastTs_;
};

////////////////////////////////////////////////
// ArrayTimeSeriesMap
////////////////////////////////////////////////

class ArrayTimeSeriesMap : public TimeSeriesMap {
  public:
  ArrayTimeSeriesMap() {}
  ~ArrayTimeSeriesMap() {}
  std::shared_ptr<MetricValue> data;
};
}

#endif
