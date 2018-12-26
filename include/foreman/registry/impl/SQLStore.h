/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTRY_SQLSTORE_H_
#define _FOREMANCC_REGISTRY_SQLSTORE_H_

#include <sqlite3.h>

#include <foreman/registry/Store.h>

namespace Foreman {
namespace Registry {

  ////////////////////////////////////////////////
  // SQLStore
  ////////////////////////////////////////////////

  class SQLStore : public Store {
public:
    SQLStore();
    virtual ~SQLStore();

    const char* getVersion();
  };

  ////////////////////////////////////////////////
  // SQLiteStore
  ////////////////////////////////////////////////

  class SQLiteStore : public SQLStore {
public:
    SQLiteStore();
    ~SQLiteStore();

    const char* getType();

    bool open();
    bool isOpened();
    bool close();
    bool clear();

    bool query(const std::string& query);
    bool prepare(const std::string& query, sqlite3_stmt** ppStmt);

    bool createObject(Object* obj, Error* err);
    bool updateObject(Object* obj, Error* err);
    bool getObject(const std::string& objId, Object* obj, Error* err);
    bool deleteObject(const std::string& objId, Error* err);

    bool browse(Query* q, Objects* objs, Error* err);
    bool search(Query* q, Objects* objs, Error* err);

protected:
    sqlite3* db_;

    bool getLastDetailError(Error* err);
  };
}
}

#endif
