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

#include <foreman/metric/impl/SQLiteStore.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// SQLiteStore
////////////////////////////////////////////////

SQLiteStore::SQLiteStore() { db_ = NULL; }

SQLiteStore::~SQLiteStore() {}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool SQLiteStore::open()
{
  if (sqlite3_open(":memory:", &db_) != SQLITE_OK)
    return false;

  return true;
}

////////////////////////////////////////////////
// isOpened
////////////////////////////////////////////////

bool SQLiteStore::isOpened()
{
  if (!db_)
    return false;

  return true;
}

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool SQLiteStore::close()
{
  if (!db_)
    return false;

  if (sqlite3_close(db_) != SQLITE_OK)
    return false;

  return true;
}

////////////////////////////////////////////////
// query
////////////////////////////////////////////////

bool SQLiteStore::query(const std::string& query)
{
  if (!isOpened())
    return false;

  char* errMsg = NULL;
  if (sqlite3_exec(db_, query.c_str(), NULL, NULL, &errMsg) != SQLITE_OK)
    return false;

  return true;
}

////////////////////////////////////////////////
// prepare
////////////////////////////////////////////////

bool SQLiteStore::prepare(const std::string& query, sqlite3_stmt** ppStmt)
{
  if (!isOpened())
    return false;

  if (sqlite3_prepare(db_, query.c_str(), (int)query.length(), ppStmt, NULL) != SQLITE_OK)
    return false;

  return true;
}
