/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_BERINGEI_TIMESERIES_H_
#define _FOREMANCC_METRIC_BERINGEI_TIMESERIES_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <foreman/metric/impl/TimeSeries.h>

#if defined(FOREMAN_ENABLE_BERINGEI)
#include <beringei/TimeSeriesStream.h>
#endif

namespace Foreman {
namespace Metric {

////////////////////////////////////////////////
// BeringeiTimeSeries
////////////////////////////////////////////////

#if defined(FOREMAN_ENABLE_BERINGEI)

  class BeringeiTimeSeries : public TimeSeries {
public:
    BeringeiTimeSeries();
    ~BeringeiTimeSeries();

    bool addValue(const Metric& m);
    bool getValues(Query* q, ResultSet* rs);

private:
    facebook::gorilla::TimeSeriesStream stream_;
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

#endif
}
}

#endif
