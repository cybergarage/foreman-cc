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

#include <foreman/MemStore.h>

using namespace Foreman;

////////////////////////////////////////////////
// SQLiteStore
////////////////////////////////////////////////

SQLiteStore::SQLiteStore() { db = NULL; }

SQLiteStore::~SQLiteStore() {}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool SQLiteStore::open()
{
  if (sqlite3_open(":memory:", &db) != SQLITE_OK)
    return false;

  return true;
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool SQLiteStore::isOpened()
{
  if (!db)
    return false;

  return true;
}

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool SQLiteStore::close()
{
  if (!db)
    return false;

  if (sqlite3_close(db) != SQLITE_OK)
    return false;

  return true;
}
