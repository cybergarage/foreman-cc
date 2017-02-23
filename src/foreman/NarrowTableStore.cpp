/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <sqlite3.h>
#include <stdio.h>

#include <foreman/Const.h>
#include <foreman/MemStore.h>

using namespace Foreman;

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

  if (!query(FOREMANCC_SQLITESOTORE_FACTOR_TABLE_DDL))
    return false;
  if (!query(FOREMANCC_SQLITESOTORE_FACTOR_INDEX_NAME_DDL))
    return false;
  if (!query(FOREMANCC_SQLITESOTORE_RECORD_TABLE_DDL))
    return false;
  if (!query(FOREMANCC_SQLITESOTORE_RECORD_INDEX_ID_DDL))
    return false;
  if (!query(FOREMANCC_SQLITESOTORE_RECORD_INDEX_TS_DDL))
    return false;

  return true;
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool NarrowTableStore::clear()
{
  if (!query(FOREMANCC_SQLITESOTORE_RECORD_TRUNCATE))
    return false;

  return true;
}

////////////////////////////////////////////////
// addMetric
////////////////////////////////////////////////

bool NarrowTableStore::addMetric(const Metric& m)
{
  sqlite3_stmt *stmt=NULL;

  // Insert a metric
  
  if (!prepare(FOREMANCC_SQLITESOTORE_FACTOR_INSERT, &stmt))
    return false;

  sqlite3_bind_text(stmt, 1, m.name.c_str(), (int)m.name.length(), SQLITE_TRANSIENT);
  if (sqlite3_step(stmt) != SQLITE_DONE) {
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);

  // Get ROWID of the inserted metric
  
  if (!prepare(FOREMANCC_SQLITESOTORE_FACTOR_SELECT_BY_NAME, &stmt))
    return false;
  
  sqlite3_bind_text(stmt, 1, m.name.c_str(), (int)m.name.length(), SQLITE_TRANSIENT);
  if (sqlite3_step(stmt) != SQLITE_ROW) {
    sqlite3_finalize(stmt);
    return false;
  }
  
  int rowId = sqlite3_column_int(stmt, 0);
  sqlite3_finalize(stmt);
  
  // Insert a metric
  
  std::shared_ptr<SQLiteMetric> sm = std::shared_ptr<SQLiteMetric>(new SQLiteMetric());
  sm->name = m.name;
  sm->rowId = rowId;
  
  metrics_.push_back(sm);
  
  return true;
}
