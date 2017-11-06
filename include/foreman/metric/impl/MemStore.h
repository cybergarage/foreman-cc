/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_MEMSTORE_H_
#define _FOREMANCC_METRIC_MEMSTORE_H_

#include <time.h>

#include <sqlite3.h>

#include <foreman/metric/Store.h>
#include <foreman/metric/impl/TimeSeriesImpl.h>
#include <foreman/net/Graphite.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // MemStore
  ////////////////////////////////////////////////

  class MemStore : public Store {
public:
    MemStore();
    virtual ~MemStore();

    virtual bool clear()
    {
      return true;
    }

    virtual bool realloc()
    {
      return true;
    }

    virtual size_t getMemoryUsage()
    {
      return 0;
    }

    virtual bool setRetentionInterval(time_t sec)
    {
      retentionInterval_ = sec;
      return true;
    };

    time_t getRetentionInterval()
    {
      return retentionInterval_;
    };

    virtual bool setRetentionPeriod(time_t sec)
    {
      retentionPeriod_ = sec;
      return true;
    };

    time_t getRetentionPeriod()
    {
      return retentionPeriod_;
    };

    size_t getColumnCount();
    size_t getRowCount();

private:
    time_t retentionInterval_;
    time_t retentionPeriod_;
  };

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

  ////////////////////////////////////////////////
  // TSmapStore
  ////////////////////////////////////////////////

  class TSmapStore : public TimeSeriesMapStore {
public:
    TSmapStore();
    ~TSmapStore();

    bool open();
    bool isOpened();
    bool close();
  };
}
}

#endif
