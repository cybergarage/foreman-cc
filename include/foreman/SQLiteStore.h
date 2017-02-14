/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_SQLITESTORE_H_
#define _FOREMANCC_SQLITESTORE_H_

#include <stdio.h>
#include <sqlite3.h>

#include <foreman/MemStore.h>

namespace Foreman {

class SQLiteStore : public MemStore {

  sqlite3 *db;
  
public:
  SQLiteStore();
  ~SQLiteStore();

  bool open();
  bool isOpened();
  bool close();
};

}

#endif
