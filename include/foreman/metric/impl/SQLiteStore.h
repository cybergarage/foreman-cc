/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_SQLITETORE_H_
#define _FOREMANCC_METRIC_SQLITETORE_H_

#include <ctime>

#include <sqlite3.h>

#include <foreman/Const.h>
#include <foreman/metric/Store.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // SQLiteStore
  ////////////////////////////////////////////////

  class SQLiteMetric : public Metric {
public:
    SQLiteMetric() {};
    int rowId;
  };

  class SQLiteStore : public Store {
public:
    SQLiteStore();
    ~SQLiteStore();

    virtual bool open();
    virtual bool close();

    bool isOpened();

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

    const char* getName() { return "sqlstore"; }
    const char* getVersion() { return FOREMANCC_PRODUCT_VERSION; }

    bool open();
    bool clear();
    bool addMetric(std::shared_ptr<Metric> m);
    bool queryMetric(Query* q, ResultSet* rs);
    bool addData(const Metric& m);
    bool addData(const MetricArray& values);
    bool queryData(Query* q, ResultSet* rs);

    virtual size_t deleteExpiredMetrics();

private:
    bool querySingleData(Query* q, ResultSet* rs);
    bool findMetric(const std::string name, int& rowId);
  };
}
}

#endif
