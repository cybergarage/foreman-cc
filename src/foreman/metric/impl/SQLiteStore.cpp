/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <cstdio>
#include <sqlite3.h>
#include <thread>

#include <foreman/metric/impl/SQLiteStore.h>
#include <foreman/log/Log.h>

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

  int retryCnt = 0;
  auto stat = sqlite3_close(db_);
  while (stat != SQLITE_OK) {
    if (stat != SQLITE_BUSY)
      return false;

    if (5 < retryCnt)
      break;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    stat = sqlite3_close(db_);
    retryCnt++;
  }

  if (stat != SQLITE_OK)
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

  lock();

  char* errMsg = NULL;
  auto rc = sqlite3_exec(db_, query.c_str(), NULL, NULL, &errMsg);

  if (rc != SQLITE_OK) {
    FOREMAN_LOG_ERROR("%s : %s (%d)", query.c_str(), errMsg, rc);
  }

  unlock();

  return (rc == SQLITE_OK) ? true : false;
}

////////////////////////////////////////////////
// prepare
////////////////////////////////////////////////

bool SQLiteStore::prepare(const std::string& query, sqlite3_stmt** ppStmt)
{
  if (!isOpened())
    return false;

  lock();

  auto rc = sqlite3_prepare(db_, query.c_str(), (int)query.length(), ppStmt, NULL);

  if (rc != SQLITE_OK) {
    FOREMAN_LOG_ERROR("%s : (%d)", query.c_str(), rc);
  }

  unlock();

  return (rc == SQLITE_OK) ? true : false;
}

////////////////////////////////////////////////
// bint
////////////////////////////////////////////////

bool SQLiteStore::bind(sqlite3_stmt* stmt, int n, const std::string& text)
{
  auto rc = sqlite3_bind_text(stmt, n, text.c_str(), (int)text.length(), SQLITE_TRANSIENT);

  if (rc != SQLITE_OK) {
    FOREMAN_LOG_ERROR("BIND( [%d] %s) : %d", n, text.c_str(), rc);
  }

  return (rc == SQLITE_OK) ? true : false;
}

bool SQLiteStore::bind(sqlite3_stmt* stmt, int n, int value)
{
  auto rc = sqlite3_bind_int(stmt, n, value);

  if (rc != SQLITE_OK) {
    FOREMAN_LOG_ERROR("BIND( [%d] %d) : %d", n, value, rc);
  }

  return (rc == SQLITE_OK) ? true : false;
}

bool SQLiteStore::bind(sqlite3_stmt* stmt, int n, double value)
{
  auto rc = sqlite3_bind_double(stmt, n, value);

  if (rc != SQLITE_OK) {
    FOREMAN_LOG_ERROR("BIND( [%d] %d) : %d", n, value, rc);
  }

  return (rc == SQLITE_OK) ? true : false;
}
