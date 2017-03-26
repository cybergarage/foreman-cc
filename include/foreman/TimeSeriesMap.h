/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_TIMESERIESMAP_H_
#define _FOREMANCC_TIMESERIESMAP_H_

#include <string>
#include <unordered_map>

#include <foreman/TimeSeries.h>

namespace Foreman {

////////////////////////////////////////////////
// TimeSeriesMap
////////////////////////////////////////////////

typedef std::pair<std::string, std::shared_ptr<TimeSeries>> TimeSeriesPair;

class TimeSeriesMap : public std::unordered_map<std::string, std::shared_ptr<TimeSeries>> {
  public:
  TimeSeriesMap();
  virtual ~TimeSeriesMap();

  std::shared_ptr<TimeSeries> findTimeSeries(const Metric& m);
  std::shared_ptr<TimeSeries> addTimeSeries(const Metric& m);
  virtual std::shared_ptr<TimeSeries> createTimeSeries(const Metric& m);

  bool addValue(const Metric& m);
  bool addValues(std::vector<std::shared_ptr<Metric>> metrics);
  bool getValues(const Metric& m, time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt);
};

////////////////////////////////////////////////
// BeringeiTimeSeriesMap
////////////////////////////////////////////////

class BeringeiTimeSeriesMap : public TimeSeriesMap {
  public:
  BeringeiTimeSeriesMap(){};
  ~BeringeiTimeSeriesMap(){};

  std::shared_ptr<TimeSeries> createTimeSeries(const Metric& m)
  {
    return std::shared_ptr<BeringeiTimeSeries>(new BeringeiTimeSeries());
  }
};
}

#endif
