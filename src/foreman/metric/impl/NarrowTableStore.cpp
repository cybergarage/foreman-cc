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
#include <cstdio>
#include <iostream>
#include <sqlite3.h>

#include <foreman/Const.h>
#include <foreman/log/Log.h>
#include <foreman/metric/impl/SQLiteStore.h>
#include <foreman/util/Util.h>

using namespace Foreman::Metric;

#define FOREMANCC_METRIC_SQLITESTORE_FACTOR_TABLE "factor"
#define FOREMANCC_METRIC_SQLITESTORE_FACTOR_NAME "name"
#define FOREMANCC_METRIC_SQLITESTORE_FACTOR_TABLE_DDL "create table if not exists factor (name text, primary key(name))"
#define FOREMANCC_METRIC_SQLITESTORE_FACTOR_INDEX_NAME_DDL "create index if not exists factor_name_idx on factor(name)"
#define FOREMANCC_METRIC_SQLITESTORE_FACTOR_INSERT "insert into factor (name) values (?)"
#define FOREMANCC_METRIC_SQLITESTORE_FACTOR_SELECT_BY_NAME "select rowid from factor where name = ?"
#define FOREMANCC_METRIC_SQLITESTORE_FACTOR_SELECT_LIKE_NAME "select name from factor where name LIKE ?"
#define FOREMANCC_METRIC_SQLITESTORE_FACTOR_SELECT_ALL "select name from factor"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_TABLE "record"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_ID "id"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_VAL "val"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_TS "ts"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_TABLE_DDL "create table if not exists record (id integer, val real, ts integer, primary key(id,ts))"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_INDEX_ID_DDL "create index if not exists record_id_idx on record(id)"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_INDEX_TS_DDL "create index if not exists record_ts_idx on record(ts)"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_INSERT "insert into record (id, val, ts) values (?, ?, ?)"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_UPDATE "update record set val = ? where id = ? and ts = ?"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_SELECT_BY_TIMESTAMP "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id and r.ts = ?"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_SELECT_BY_FACTOR "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id and f.name = ?"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_SELECT_BY_FACTOR_BETWEEN_TIMESTAMP "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id and f.name = ? and ts between ? and ?"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_SELECT_ALL "select f.name, r.val, r.ts from factor f, record r where f.rowid = r.id"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_TRUNCATE "delete from record"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_TRUNCATE_BY_TIME "delete from record where ts < ?"
#define FOREMANCC_METRIC_SQLITESTORE_RECORD_RECORD_COUNT "select count(*) from record"

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

  if (!query(FOREMANCC_METRIC_SQLITESTORE_FACTOR_TABLE_DDL))
    return false;
  if (!query(FOREMANCC_METRIC_SQLITESTORE_FACTOR_INDEX_NAME_DDL))
    return false;
  if (!query(FOREMANCC_METRIC_SQLITESTORE_RECORD_TABLE_DDL))
    return false;
  if (!query(FOREMANCC_METRIC_SQLITESTORE_RECORD_INDEX_ID_DDL))
    return false;
  if (!query(FOREMANCC_METRIC_SQLITESTORE_RECORD_INDEX_TS_DDL))
    return false;

  return true;
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool NarrowTableStore::clear()
{
  if (!query(FOREMANCC_METRIC_SQLITESTORE_RECORD_TRUNCATE))
    return false;
  return true;
}

////////////////////////////////////////////////
// addMetric
////////////////////////////////////////////////

bool NarrowTableStore::addMetric(std::shared_ptr<Metric> m)
{
  // Insert a metric

  sqlite3_stmt* stmt = NULL;
  if (!prepare(FOREMANCC_METRIC_SQLITESTORE_FACTOR_INSERT, &stmt)) {
    return false;
  }

  if (!bind(stmt, 1, m->name)) {
    sqlite3_finalize(stmt);
    return false;
  }

  lock();

  auto rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  unlock();

  if (rc != SQLITE_DONE) {
    FOREMAN_LOG_ERROR("%s (%s)", FOREMANCC_METRIC_SQLITESTORE_FACTOR_INSERT, m->name.c_str());
    return false;
  }

  // Get ROWID of the inserted metric

  int rowId = -1;
  if (!findMetric(m->name, rowId))
    return false;

  FOREMAN_LOG_DEBUG("%s (%s:%d)", FOREMANCC_METRIC_SQLITESTORE_FACTOR_INSERT, m->name.c_str(), rowId);

  return true;
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
    if (!prepare(FOREMANCC_METRIC_SQLITESTORE_FACTOR_SELECT_LIKE_NAME, &stmt)) {
      return false;
    }

    // Replace '*' to '%" for Graphite query.
    auto target = q->target;
    std::replace(target.begin(), target.end(), '*', '%');

    if (!bind(stmt, 1, target)) {
      sqlite3_finalize(stmt);
      return false;
    }
  }
  else {
    if (!prepare(FOREMANCC_METRIC_SQLITESTORE_FACTOR_SELECT_ALL, &stmt)) {
      return false;
    }
  }

  lock();

  auto rc = sqlite3_step(stmt);

  if (rc == SQLITE_ROW) {
    FOREMAN_LOG_DEBUG("%s (%s) : %d", FOREMANCC_METRIC_SQLITESTORE_FACTOR_SELECT_LIKE_NAME, q->target.c_str(), rc);
  }
  else {
    FOREMAN_LOG_DEBUG("%s (%s) : %d", FOREMANCC_METRIC_SQLITESTORE_FACTOR_SELECT_LIKE_NAME, q->target.c_str(), rc);
  }

  size_t rowCnt = 1;

  while (rc == SQLITE_ROW) {
    auto name = sqlite3_column_text(stmt, 0);
    if (!name)
      continue;

    auto ms = std::shared_ptr<Metrics>(new Metrics());
    ms->setName((const char*)name);
    if (!rs->addMetrics(ms)) {
      sqlite3_finalize(stmt);
      unlock();
      return false;
    }

    FOREMAN_LOG_DEBUG("[%d] %s (%s) : %d (%s)", rowCnt, FOREMANCC_METRIC_SQLITESTORE_FACTOR_SELECT_LIKE_NAME, q->target.c_str(), rc, name);

    rc = sqlite3_step(stmt);
    rowCnt++;
  }

  sqlite3_finalize(stmt);

  unlock();

  return true;
}

////////////////////////////////////////////////
// addData
////////////////////////////////////////////////

bool NarrowTableStore::addData(const Metric& m)
{
  int rowId = -1;
  if (!findMetric(m.name, rowId))
    return false;

  // Revise Timestamp

  auto metricTs = m.timestamp - (m.timestamp % getRetentionInterval());

  // Insert a value

  sqlite3_stmt* stmt = NULL;

  if (!prepare(FOREMANCC_METRIC_SQLITESTORE_RECORD_INSERT, &stmt)) {
    return false;
  }
  if (!bind(stmt, 1, rowId)) {
    sqlite3_finalize(stmt);
    return false;
  }
  if (!bind(stmt, 2, m.value)) {
    sqlite3_finalize(stmt);
    return false;
  }
  if (!bind(stmt, 3, (int)metricTs)) {
    sqlite3_finalize(stmt);
    return false;
  }

  lock();

  auto rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  unlock();

  if (rc == SQLITE_DONE) {
    FOREMAN_LOG_DEBUG("%s (%s:%d, %lf, %d) : %d", FOREMANCC_METRIC_SQLITESTORE_RECORD_INSERT, m.name.c_str(), rowId, m.value, (int)metricTs, rc);
    return true;
  }

  // Update the inserted value

  if (!prepare(FOREMANCC_METRIC_SQLITESTORE_RECORD_UPDATE, &stmt)) {
    return false;
  }
  if (!bind(stmt, 1, m.value)) {
    sqlite3_finalize(stmt);
    return false;
  }
  if (!bind(stmt, 2, rowId)) {
    sqlite3_finalize(stmt);
    return false;
  }
  if (!bind(stmt, 3, (int)metricTs)) {
    sqlite3_finalize(stmt);
    return false;
  }

  lock();

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  unlock();

  if (rc == SQLITE_DONE) {
    FOREMAN_LOG_DEBUG("%s (%s:%d, %lf, %d) : %d", FOREMANCC_METRIC_SQLITESTORE_RECORD_UPDATE, m.name.c_str(), rowId, m.value, (int)metricTs, rc);
  }
  else {
    FOREMAN_LOG_DEBUG("%s (%lf, %s:%d, %d)", FOREMANCC_METRIC_SQLITESTORE_RECORD_UPDATE, m.value, m.name.c_str(), rowId, (int)metricTs);
  }

  return (rc == SQLITE_DONE) ? true : false;
}

bool NarrowTableStore::addData(const MetricArray& values)
{
  for (auto m : values) {
    if (!addData(*m))
      return false;
  }
  return true;
}

////////////////////////////////////////////////
// queryData
////////////////////////////////////////////////

bool NarrowTableStore::querySingleData(Query* q, ResultSet* rs)
{
  if (!q || !rs)
    return false;

  if (q->until <= q->from) {
    FOREMAN_LOG_ERROR("%s (%s, %d, %d, %d) : until(%d) <= from(%d)", FOREMANCC_METRIC_SQLITESTORE_RECORD_SELECT_BY_FACTOR_BETWEEN_TIMESTAMP, q->target.c_str(), (int)q->from, (int)q->until, q->interval, (int)q->until, (int)q->from);
    return false;
  }

  if (q->interval == 0) {
    FOREMAN_LOG_ERROR("%s (%s, %d, %d, %d) : interval == %d", FOREMANCC_METRIC_SQLITESTORE_RECORD_SELECT_BY_FACTOR_BETWEEN_TIMESTAMP, q->target.c_str(), (int)q->from, (int)q->until, q->interval, q->interval);
    return false;
  }

  ssize_t valueCount = (q->until - q->from) / q->interval;
  if (valueCount <= 0) {
    FOREMAN_LOG_ERROR("%s (%s, %d, %d, %d) : value count == %d", FOREMANCC_METRIC_SQLITESTORE_RECORD_SELECT_BY_FACTOR_BETWEEN_TIMESTAMP, q->target.c_str(), (int)q->from, (int)q->until, q->interval, 0);
    return false;
  }

  double* values = CreateNanDataPointValueArray(valueCount);
  if (!values)
    return false;

  // Select values

  sqlite3_stmt* stmt = NULL;
  if (!prepare(FOREMANCC_METRIC_SQLITESTORE_RECORD_SELECT_BY_FACTOR_BETWEEN_TIMESTAMP, &stmt)) {
    unlock();
    return false;
  }
  if (!bind(stmt, 1, q->target)) {
    sqlite3_finalize(stmt);
    return false;
  }
  if (!bind(stmt, 2, (int)q->from)) {
    sqlite3_finalize(stmt);
    return false;
  }
  if (!bind(stmt, 3, (int)q->until)) {
    sqlite3_finalize(stmt);
    return false;
  }

  lock();

  auto rc = sqlite3_step(stmt);

  if (rc == SQLITE_ROW) {
    FOREMAN_LOG_DEBUG("%s (%s, %d, %d, %d) : %d", FOREMANCC_METRIC_SQLITESTORE_RECORD_SELECT_BY_FACTOR_BETWEEN_TIMESTAMP, q->target.c_str(), (int)q->from, (int)q->until, q->interval, rc);
  }
  else {
    FOREMAN_LOG_DEBUG("%s (%s, %d, %d, %d) : %d", FOREMANCC_METRIC_SQLITESTORE_RECORD_SELECT_BY_FACTOR_BETWEEN_TIMESTAMP, q->target.c_str(), (int)q->from, (int)q->until, q->interval, rc);
  }

  size_t rowCont = 1;
  while (rc == SQLITE_ROW) {
    double value = sqlite3_column_double(stmt, 1);
    time_t valueTs = sqlite3_column_int(stmt, 2);
    ssize_t valueIdx = (valueTs - q->from) / q->interval;
    if ((0 <= valueIdx) && (valueIdx < valueCount)) {
      values[valueIdx] = value;
    }

    FOREMAN_LOG_DEBUG("[%d] %s (%s, %lf, %d) : %d", rowCont, FOREMANCC_METRIC_SQLITESTORE_RECORD_SELECT_BY_FACTOR_BETWEEN_TIMESTAMP, q->target.c_str(), value, valueTs, rc);

    rc = sqlite3_step(stmt);
    rowCont++;
  }

  sqlite3_finalize(stmt);

  unlock();

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

////////////////////////////////////////////////
// deleteExpiredMetrics
////////////////////////////////////////////////

size_t NarrowTableStore::deleteExpiredMetrics()
{
  if (!isOpened())
    return 0;

  int ts = int(std::time(nullptr) - getRetentionPeriod());

  sqlite3_stmt* stmt = NULL;
  if (!prepare(FOREMANCC_METRIC_SQLITESTORE_RECORD_TRUNCATE_BY_TIME, &stmt)) {
    return 0;
  }
  if (!bind(stmt, 1, ts)) {
    sqlite3_finalize(stmt);
    return false;
  }

  lock();

  auto rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  if (rc != SQLITE_DONE) {
    FOREMAN_LOG_ERROR("%s (%d) : %d", FOREMANCC_METRIC_SQLITESTORE_RECORD_TRUNCATE_BY_TIME, ts, rc);
    return 0;
  }
  else {
    FOREMAN_LOG_DEBUG("%s (%d) : %d", FOREMANCC_METRIC_SQLITESTORE_RECORD_TRUNCATE_BY_TIME, ts, rc);
  }

  size_t nRows = sqlite3_changes(db_);

  unlock();

  return nRows;
}

bool NarrowTableStore::findMetric(const std::string name, int& rowId)
{
  if (!isOpened())
    return 0;

  sqlite3_stmt* stmt = NULL;
  if (!prepare(FOREMANCC_METRIC_SQLITESTORE_FACTOR_SELECT_BY_NAME, &stmt)) {
    return false;
  }
  if (!bind(stmt, 1, name)) {
    sqlite3_finalize(stmt);
    return false;
  }

  lock();

  auto rc = sqlite3_step(stmt);

  if (rc == SQLITE_ROW) {
    rowId = sqlite3_column_int(stmt, 0);
  }

  sqlite3_finalize(stmt);

  unlock();

  if (rc == SQLITE_ROW) {
    FOREMAN_LOG_DEBUG("%s (%s:%d) : %d", FOREMANCC_METRIC_SQLITESTORE_FACTOR_SELECT_BY_NAME, name.c_str(), rowId, rc);
  }
  else {
    FOREMAN_LOG_DEBUG("%s (%s) : %d", FOREMANCC_METRIC_SQLITESTORE_FACTOR_SELECT_BY_NAME, name.c_str(), rc);
  }

  return (rc == SQLITE_ROW) ? true : false;
}
