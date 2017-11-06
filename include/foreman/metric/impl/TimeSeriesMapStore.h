/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_TIMESERIESMAP_STORE_H_
#define _FOREMANCC_METRIC_TIMESERIESMAP_STORE_H_

#include <time.h>

#include <sqlite3.h>

#include <foreman/metric/impl/ArrayTimeSeries.h>
#include <foreman/metric/impl/MemStore.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // TimeSeriesMapStore
  ////////////////////////////////////////////////

  class TimeSeriesMapStore : public MemStore {
public:
    TimeSeriesMapStore();
    virtual ~TimeSeriesMapStore();

    bool addValue(const Metric& m);
    bool getValues(Query* q, ResultSet* rs);

protected:
    std::shared_ptr<TimeSeriesMap> tsMap_;
  };

  ////////////////////////////////////////////////
  // MatrixStore
  ////////////////////////////////////////////////

  class MatrixTimeSeries : public StaticArrayTimeSeries {
public:
    MatrixTimeSeries(){};
    ~MatrixTimeSeries(){};
  };

  class MatrixStore : public TimeSeriesMapStore {
public:
    MatrixStore();
    ~MatrixStore();

    bool open();
    bool isOpened();
    bool close();

    bool realloc();
  };

  ////////////////////////////////////////////////
  // RingMapStore
  ////////////////////////////////////////////////

  class RingMapTimeSeries : public RingArrayTimeSeries {
public:
    RingMapTimeSeries(){};
    ~RingMapTimeSeries(){};
  };

  class RingMapStore : public TimeSeriesMapStore {
public:
    RingMapStore();
    ~RingMapStore();

    bool open();
    bool isOpened();
    bool close();
    bool realloc();
  };
}
}

#endif
