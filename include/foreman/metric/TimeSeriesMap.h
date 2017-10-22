/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_TIMESERIESMAP_H_
#define _FOREMANCC_TIMESERIESMAP_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>
#include <unordered_map>

#include <foreman/metric/Query.h>
#include <foreman/metric/ResultSet.h>
#include <foreman/metric/TimeSeries.h>

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
  bool getValues(Query* q, ResultSet* rs);
};

////////////////////////////////////////////////
// BeringeiTimeSeriesMap
////////////////////////////////////////////////

#if defined(FOREMAN_ENABLE_BERINGEI)

class BeringeiTimeSeriesMap : public TimeSeriesMap {
  public:
  BeringeiTimeSeriesMap(){};
  ~BeringeiTimeSeriesMap(){};

  std::shared_ptr<TimeSeries> createTimeSeries(const Metric& m)
  {
    return std::shared_ptr<BeringeiTimeSeries>(new BeringeiTimeSeries());
  }
};

#endif
}

#endif
