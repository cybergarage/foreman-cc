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

  virtual bool addMetric(std::shared_ptr<Metric> m);
  std::shared_ptr<Metric> findMetric(const std::string& name);
  std::shared_ptr<std::vector<std::shared_ptr<Metric> > > getMetrics();

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
  MetricMap metricMap_;

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
  bool getValues(const Metric& m, time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt);

  protected:
  std::shared_ptr<TimeSeriesMap> tsMap_;
};

////////////////////////////////////////////////
// SQLiteStore
////////////////////////////////////////////////

class SQLiteMetric : public Metric {
  public:
  SQLiteMetric(){};
  int rowId;
};

class SQLiteStore : public MemStore {
  public:
  SQLiteStore();
  ~SQLiteStore();

  virtual bool open();

  bool isOpened();
  bool close();

  bool query(const std::string& query);
  bool prepare(const std::string& query, sqlite3_stmt** ppStmt);

  protected:
  sqlite3* db_;
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
  bool addMetric(std::shared_ptr<Metric> m);
  bool addValue(const Metric& m);
  bool getValues(const Metric& m, time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<MetricValue>& values, size_t& valueCnt);
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

class TSmapTimeSeries : public BeringeiTimeSeries {
public:
  TSmapTimeSeries(){};
  ~TSmapTimeSeries(){};
};

class TSmapStore : public TimeSeriesMapStore {
public:
  TSmapStore();
  ~TSmapStore();
  
  bool open();
  bool isOpened();
  bool close();
};
  
}

#endif
