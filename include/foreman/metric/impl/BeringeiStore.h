/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_BERINGEI_STORE_H_
#define _FOREMANCC_METRIC_BERINGEI_STORE_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <foreman/metric/Store.h>
#include <foreman/metric/impl/TimeSeries.h>
#include <foreman/metric/impl/TimeSeriesMapStore.h>

#if defined(FOREMAN_ENABLE_BERINGEI)
#include <beringei/TimeSeriesStream.h>
#endif

namespace Foreman {
namespace Metric {

#if defined(FOREMAN_ENABLE_BERINGEI)

  ////////////////////////////////////////////////
  // BeringeiStore
  ////////////////////////////////////////////////

  class BeringeiStore : public TimeSeriesMapStore {
public:
    BeringeiStore();
    ~BeringeiStore();

    bool open();
    bool close();
  };

  ////////////////////////////////////////////////
  // BeringeiTimeSeries
  ////////////////////////////////////////////////

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
}

#endif
