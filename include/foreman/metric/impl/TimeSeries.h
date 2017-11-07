/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_TIMESERIES_H_
#define _FOREMANCC_METRIC_TIMESERIES_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <foreman/metric/Metric.h>
#include <foreman/metric/Query.h>
#include <foreman/metric/ResultSet.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // TimeSeries
  ////////////////////////////////////////////////

  class TimeSeries {
public:
    TimeSeries();
    virtual ~TimeSeries();

    virtual bool addValue(const Metric& m) = 0;
    virtual bool getValues(Query* q, ResultSet* rs) = 0;
  };

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
}
}

#endif
