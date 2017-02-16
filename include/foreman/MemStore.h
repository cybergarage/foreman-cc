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

#include <time.h>

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

  virtual bool setRetentionInterval(time_t sec)
  {
    retentionInterval_ = sec;
    return true;
  };

  virtual bool setRetentionPeriod(time_t sec)
  {
    retentionPeriod_ = sec;
    return true;
  };

  private:
  time_t retentionInterval_;
  time_t retentionPeriod_;
};

////////////////////////////////////////////////
// WideTableStore
////////////////////////////////////////////////

class SQLiteStore : public MemStore {
  public:
  SQLiteStore();
  ~SQLiteStore();

  bool open();
  bool isOpened();
  bool close();

private:
  sqlite3* db;  
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

////////////////////////////////////////////////
// MatrixStore
////////////////////////////////////////////////

class MatrixStore : public MemStore {
  public:
  MatrixStore();
  ~MatrixStore();

  bool open();
  bool isOpened();
  bool close();
};

////////////////////////////////////////////////
// RingMapStore
////////////////////////////////////////////////

class RingMapStore : public MemStore {
  public:
  RingMapStore();
  ~RingMapStore();

  bool open();
  bool isOpened();
  bool close();
};
}

#endif
