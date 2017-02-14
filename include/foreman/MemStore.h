/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_MEMSTORE_H_
#define _FOREMANCC_MEMSTORE_H_

#include <sqlite3.h>

#include <foreman/Platform.h>

namespace Foreman {

////////////////////////////////////////////////
// MemStore
////////////////////////////////////////////////

class MemStore {

public:
  MemStore();
  virtual ~MemStore();
  
  virtual bool open() = 0;
  virtual bool isOpened() = 0;
  virtual bool close() = 0;
};

////////////////////////////////////////////////
// WideTableStore
////////////////////////////////////////////////

class SQLiteStore : public MemStore {

  sqlite3 *db;
  
public:
  SQLiteStore();
  ~SQLiteStore();

  bool open();
  bool isOpened();
  bool close();
};

class WideTableStore : public SQLiteStore {
  
public:
  WideTableStore();
  ~WideTableStore();

  bool open();
};

////////////////////////////////////////////////
// TSmapStore
////////////////////////////////////////////////

class TSmapStore : public MemStore {

public:
  TSmapStore();
  ~TSmapStore();

  bool open();
  bool isOpened();
  bool close();
};

}

#endif
