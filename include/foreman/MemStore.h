/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_MEMSTORE_H_
#define _FOREMANCC_MEMSTORE_H_

#include <time.h>

#include <sqlite3.h>

#include <foreman/Store.h>
#include <foreman/TimeSeriesMap.h>
#include <foreman/net/Graphite.h>

namespace Foreman {

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
  bool getValues(Query* q, ResultSet* rs);
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

////////////////////////////////////////////////
// GraphiteStore
////////////////////////////////////////////////

class GraphiteStore : public MemStore {
  public:
  GraphiteStore();
  ~GraphiteStore();

  bool open();
  bool isOpened();
  bool close();

  void setHost(const std::string& host);
  void setCarbonPort(int port);
  void setHttpPort(int port);

  bool addValue(const Metric& m);
  bool getValues(Query* q, ResultSet* rs);

  private:
  Graphite graphite;
};
}

#endif
