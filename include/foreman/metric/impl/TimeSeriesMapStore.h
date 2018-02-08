/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_TIMESERIESMAP_STORE_H_
#define _FOREMANCC_METRIC_TIMESERIESMAP_STORE_H_

#include <foreman/metric/impl/MemStore.h>
#include <foreman/metric/impl/TimeSeries.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // TimeSeriesMapStore
  ////////////////////////////////////////////////

  class TimeSeriesMapStore : public MemStore {
public:
    TimeSeriesMapStore();
    virtual ~TimeSeriesMapStore();

    bool getData(const Metric& m);
    bool queryData(Query* q, ResultSet* rs);

protected:
    std::shared_ptr<TimeSeriesMap> tsMap_;
  };
}
}

#endif
