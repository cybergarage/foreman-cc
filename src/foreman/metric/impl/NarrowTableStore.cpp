/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <algorithm>
#include <sqlite3.h>
#include <stdio.h>

#include <foreman/Const.h>
#include <foreman/metric/impl/SQLiteStore.h>
#include <foreman/util/Util.h>

using namespace Foreman::Metric;

#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_TABLE "factor"
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_NAME "name"
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_TABLE_DDL "create table if not exists factor (name text, primary key(name))"
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_INDEX_NAME_DDL "create index if not exists factor_name_idx on factor(name)"
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_INSERT "insert into factor (name) values (?)"
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_SELECT_BY_NAME "select rowid from factor where name = ?"
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_SELECT_LIKE_NAME "select name from factor where name LIKE ?"
#define FOREMANCC_METRIC_SQLITESOTORE_FACTOR_SELECT_ALL "select name from factor"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_TABLE "record"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_ID "id"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_VAL "val"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_TS "ts"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_TABLE_DDL "create table if not exists record (id integer, val real, ts integer, primary key(id,ts))"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_INDEX_ID_DDL "create index if not exists record_id_idx on record(id)"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_INDEX_TS_DDL "create index if not exists record_ts_idx on record(ts)"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_INSERT "insert into record (id, val, ts) values (?, ?, ?)"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_UPDATE "update record set val = ? where id = ? and ts = ?"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_SELECT_BY_TIMESTAMP "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id and r.ts = ?"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_SELECT_BY_FACTOR "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id and f.name = ?"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_SELECT_BY_FACTOR_BETWEEN_TIMESTAMP "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id and f.name = ? and ts between ? and ?"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_SELECT_ALL "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_TRUNCATE "delete from record"
#define FOREMANCC_METRIC_SQLITESOTORE_RECORD_TRUNCATE_BY_TIME "delete from record where ts < ?"

////////////////////////////////////////////////
// NarrowTableStore
////////////////////////////////////////////////

NarrowTableStore::NarrowTableStore() {}

NarrowTableStore::~NarrowTableStore() {}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool NarrowTableStore::open()
{
  if (!SQLiteStore::open())
    return false;

  if (!query(FOREMANCC_METRIC_SQLITESOTORE_FACTOR_TABLE_DDL))
    return false;
  if (!query(FOREMANCC_METRIC_SQLITESOTORE_FACTOR_INDEX_NAME_DDL))
    return false;
  if (!query(FOREMANCC_METRIC_SQLITESOTORE_RECORD_TABLE_DDL))
    return false;
  if (!query(FOREMANCC_METRIC_SQLITESOTORE_RECORD_INDEX_ID_DDL))
    return false;
  if (!query(FOREMANCC_METRIC_SQLITESOTORE_RECORD_INDEX_TS_DDL))
    return false;

  return true;
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool NarrowTableStore::clear()
{
  if (!query(FOREMANCC_METRIC_SQLITESOTORE_RECORD_TRUNCATE))
    return false;

  return true;
}

////////////////////////////////////////////////
// addMetric
////////////////////////////////////////////////

bool NarrowTableStore::addMetric(std::shared_ptr<Metric> m)
{
  sqlite3_stmt* stmt = NULL;

  // Insert a metric

  if (!prepare(FOREMANCC_METRIC_SQLITESOTORE_FACTOR_INSERT, &stmt))
    return false;

  sqlite3_bind_text(stmt, 1, m->name.c_str(), (int)m->name.length(), SQLITE_TRANSIENT);
  if (sqlite3_step(stmt) != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);

  // Get ROWID of the inserted metric

  if (!prepare(FOREMANCC_METRIC_SQLITESOTORE_FACTOR_SELECT_BY_NAME, &stmt))
    return false;

  sqlite3_bind_text(stmt, 1, m->name.c_str(), (int)m->name.length(), SQLITE_TRANSIENT);
  if (sqlite3_step(stmt) != SQLITE_ROW) {
    sqlite3_finalize(stmt);
    return false;
  }

  int rowId = sqlite3_column_int(stmt, 0);
  sqlite3_finalize(stmt);

  // Insert a metric

  SQLiteMetric* sm = new SQLiteMetric();
  if (!sm)
    return false;
  sm->name = m->name;
  sm->rowId = rowId;
  return MemStore::addMetric(std::shared_ptr<Foreman::Metric::Metric>(sm));
}

////////////////////////////////////////////////
// queryMetric
////////////////////////////////////////////////

bool NarrowTableStore::queryMetric(Query* q, ResultSet* rs)
{
  if (!q || !rs)
    return false;

  sqlite3_stmt* stmt = NULL;

  if (q->hasTarget()) {
    if (!prepare(FOREMANCC_METRIC_SQLITESOTORE_FACTOR_SELECT_LIKE_NAME, &stmt))
      return false;

    // Replace '*' to '%" for Graphite query.
    auto target = q->target;
    std::replace(target.begin(), target.end(), '*', '%');
    sqlite3_bind_text(stmt, 1, target.c_str(), (int)target.length(), SQLITE_TRANSIENT);
  }
  else {
    if (!prepare(FOREMANCC_METRIC_SQLITESOTORE_FACTOR_SELECT_ALL, &stmt))
      return false;
  }

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    auto name = sqlite3_column_text(stmt, 0);
    if (!name)
      continue;
    auto ms = std::shared_ptr<Metrics>(new Metrics);
    ms->setName((const char*)name);
    if (!rs->addMetrics(ms))
      return false;
  }

  sqlite3_finalize(stmt);

  return true;
}

////////////////////////////////////////////////
// addData
////////////////////////////////////////////////

bool NarrowTableStore::addData(const Metric& m)
{
  std::shared_ptr<Metric> mm = findMetric(m.name);
  if (!mm)
    return false;

  SQLiteMetric* sm = dynamic_cast<SQLiteMetric*>(mm.get());
  if (!sm)
    return false;

  int rowId = sm->rowId;

  // Revise Timestamp

  time_t metricTs = m.timestamp;

  // Insert a value

  sqlite3_stmt* stmt = NULL;

  if (!prepare(FOREMANCC_METRIC_SQLITESOTORE_RECORD_INSERT, &stmt))
    return false;

  sqlite3_bind_int(stmt, 1, rowId);
  sqlite3_bind_double(stmt, 2, m.value);
  sqlite3_bind_int(stmt, 3, (int)metricTs);

  if (sqlite3_step(stmt) == SQLITE_DONE) {
    sqlite3_finalize(stmt);
    return true;
  }

  sqlite3_finalize(stmt);

  // Update a value

  if (!prepare(FOREMANCC_METRIC_SQLITESOTORE_RECORD_UPDATE, &stmt))
    return false;

  sqlite3_bind_double(stmt, 1, m.value);
  sqlite3_bind_int(stmt, 2, rowId);
  sqlite3_bind_int(stmt, 3, (int)m.timestamp);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);

  return true;
}

////////////////////////////////////////////////
// queryData
////////////////////////////////////////////////

bool NarrowTableStore::querySingleData(Query* q, ResultSet* rs)
{
  if (!q || !rs)
    return false;

  if (q->until <= q->from)
    return false;

  if (q->interval == 0)
    return false;

  ssize_t valueCount = (q->until - q->from) / q->interval;
  if (valueCount <= 0)
    return false;

  double* values = CreateNanDataPointValueArray(valueCount);
  if (!values)
    return false;

  // Select values

  sqlite3_stmt* stmt = NULL;

  if (!prepare(FOREMANCC_METRIC_SQLITESOTORE_RECORD_SELECT_BY_FACTOR_BETWEEN_TIMESTAMP, &stmt))
    return false;

  sqlite3_bind_text(stmt, 1, q->target.c_str(), (int)q->target.length(), SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 2, (int)q->from);
  sqlite3_bind_int(stmt, 3, (int)q->until);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    double value = sqlite3_column_double(stmt, 1);
    time_t valueTs = sqlite3_column_int(stmt, 2);
    ssize_t valueIdx = (valueTs - q->from) / q->interval;
    if (valueIdx < 0 || valueCount <= valueIdx)
      continue;
    values[valueIdx] = value;
  }
  sqlite3_finalize(stmt);

  bool isSuccess = rs->addMetrics(q->getTarget(), q->getFrom(), q->getInterval(), values, valueCount);

  delete[] values;

  return isSuccess;
}

bool NarrowTableStore::queryData(Query* q, ResultSet* dataRs)
{
  if (!q || !dataRs)
    return false;

  ResultSet metricsRs;
  if (!queryMetric(q, &metricsRs))
    return false;

  Query dataQuery = *q;
  auto m = metricsRs.firstMetrics();
  while (m) {
    dataQuery.setTarget(m->getName());
    if (!querySingleData(&dataQuery, dataRs))
      return false;
    m = metricsRs.nextMetrics();
  }

  return true;
}

size_t NarrowTableStore::deleteExpiredMetrics()
{
  if (!isOpened())
    return 0;
  sqlite3_stmt* stmt = NULL;
  if (!prepare(FOREMANCC_METRIC_SQLITESOTORE_RECORD_TRUNCATE_BY_TIME, &stmt))
    return 0;
  sqlite3_bind_int(stmt, 1, std::time(nullptr) - getRetentionPeriod());
  if (sqlite3_step(stmt) != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    return 0;
  }

  return sqlite3_changes(db_);
}
