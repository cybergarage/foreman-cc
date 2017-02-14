/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdio.h>
#include <sqlite3.h>

#include <foreman/SQLiteStore.h>

using namespace Foreman;

////////////////////////////////////////////////
// SQLiteStore
////////////////////////////////////////////////

SQLiteStore::SQLiteStore() {
  db = NULL;
}

SQLiteStore::~SQLiteStore() {
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool SQLiteStore::open() {
  if (sqlite3_open("", &db) != SQLITE_OK)
    return false;
  return true;
}

////////////////////////////////////////////////
// open
////////////////////////////////////////////////

bool SQLiteStore::isOpened() {
  if (!db)
    return false;
  return true;
}

////////////////////////////////////////////////
// close
////////////////////////////////////////////////

bool SQLiteStore::close() {
  if (!db)
    return false;
  sqlite3_close(db);
  return true;
}
