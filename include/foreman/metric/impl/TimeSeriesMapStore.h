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

#include <foreman/metric/Store.h>
#include <foreman/metric/impl/TimeSeries.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // TimeSeriesMapStore
  ////////////////////////////////////////////////

  class TimeSeriesMapStore : public Store {
protected:
    std::shared_ptr<TimeSeriesMap> tsMap_;
    size_t getColumnCount();

public:
    TimeSeriesMapStore();
    virtual ~TimeSeriesMapStore();

    bool addMetric(std::shared_ptr<Metric> m);
    bool queryMetric(Query* q, ResultSet* rs);

    bool addData(const Metric& m);
    bool addData(const MetricArray& values);
    bool queryData(Query* q, ResultSet* rs);

    virtual void clear()
    {
      tsMap_->clear();
    }
  };
}
}

#endif
