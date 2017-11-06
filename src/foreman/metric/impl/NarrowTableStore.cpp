/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <sqlite3.h>
#include <stdio.h>

#include <foreman/Const.h>
#include <foreman/metric/impl/SQLiteStore.h>
#include <foreman/util/Util.h>

using namespace Foreman::Metric;

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
// addValue
////////////////////////////////////////////////

bool NarrowTableStore::addValue(const Metric& m)
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
  time_t retentionInterval = getRetentionPeriod();
  if ((0 < retentionInterval) && (retentionInterval < metricTs)) {
    metricTs -= (metricTs / retentionInterval);
  }

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
// getValues
////////////////////////////////////////////////

bool NarrowTableStore::getValues(Query* q, ResultSet* rs)
{
  if (!q || !rs)
    return false;

  if (q->until <= q->from)
    return false;

  size_t valueCount = (q->until - q->from) / q->interval;
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

  bool isSuccess = rs->addDataPoints(q->getTarget(), q->getFrom(), q->getInterval(), values, valueCount);

  delete[] values;

  return isSuccess;
}
