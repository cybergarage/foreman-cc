/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_MEMSTORE_H_
#define _FOREMANCC_MEMSTORE_H_

#include <time.h>

#include <sqlite3.h>

#include <foreman/Metric.h>
#include <foreman/TimeSeries.h>

namespace Foreman {

////////////////////////////////////////////////
// MemStore
////////////////////////////////////////////////

class MemStore {
  public:
  MemStore();
  virtual ~MemStore();

  virtual bool open() = 0;
  virtual bool isOpened() = 0;
  virtual bool close() = 0;
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

  virtual bool addMetric(const Metric& m);

  virtual Metrics& getMetrics()
  {
    return metrics_;
  }

  virtual bool addValue(const Metric& value)
  {
    return true;
  }

  virtual bool addValues(const Metrics& values);

  virtual bool getValues(const Metric& m, time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt)
  {
    return true;
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

  protected:
  Metrics metrics_;

  private:
  time_t retentionInterval_;
  time_t retentionPeriod_;
};

////////////////////////////////////////////////
// TimeSeriesMapStore
////////////////////////////////////////////////

template <typename TimeSeriesMapType>
class TimeSeriesMapStoreTemplate : public MemStore {
  public:
  TimeSeriesMapStoreTemplate(){};
  virtual ~TimeSeriesMapStoreTemplate(){};

  bool addValue(const Metric& m) { return tsMap_->addValue(m); }
  bool getValues(const Metric& m, time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt) { return tsMap_->getValues(m, beginTs, endTs, interval, values, valueCnt); }

  protected:
  std::shared_ptr<TimeSeriesMapType> tsMap_;
};

class TimeSeriesMapStore : public TimeSeriesMapStoreTemplate<TimeSeriesMap> {
  public:
  TimeSeriesMapStore(){};
  virtual ~TimeSeriesMapStore(){};
};

////////////////////////////////////////////////
// SQLiteStore
////////////////////////////////////////////////

class SQLiteStore : public MemStore {
  public:
  SQLiteStore();
  ~SQLiteStore();

  virtual bool open();

  bool isOpened();
  bool close();
  bool query(const std::string& query);

  protected:
  sqlite3* db_;
};

////////////////////////////////////////////////
// WideTableStore
////////////////////////////////////////////////

class WideTableStore : public SQLiteStore {
  public:
  WideTableStore();
  ~WideTableStore();

  bool open();
};

////////////////////////////////////////////////
// NarrowTableStore
////////////////////////////////////////////////

class NarrowTableStore : public SQLiteStore {
  public:
  NarrowTableStore();
  ~NarrowTableStore();

  bool open();
  bool clear();
  bool addMetric(const Metric& m);
};

////////////////////////////////////////////////
// TSmapStore
////////////////////////////////////////////////

class TSmapStore : public MemStore {
  public:
  TSmapStore();
  ~TSmapStore();

  bool open();
  bool isOpened();
  bool close();
};

////////////////////////////////////////////////
// MatrixStore
////////////////////////////////////////////////

class MatrixTimeSeriesMap : public TimeSeriesMap {
  public:
  MatrixTimeSeriesMap() {}
  ~MatrixTimeSeriesMap() {}
  std::shared_ptr<MetricValue> mxValues;
};

class MatrixTimeSeries : public ArrayTimeSeries {
  public:
  MatrixTimeSeries(){};
  ~MatrixTimeSeries(){};
};

class MatrixStore : public TimeSeriesMapStoreTemplate<MatrixTimeSeriesMap> {
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

class RingMapTimeSeriesMap : public TimeSeriesMap {
  public:
  RingMapTimeSeriesMap() {}
  ~RingMapTimeSeriesMap() {}
};

class RingMapTimeSeries : public ArrayTimeSeries {
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

#endif
