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

    bool query(const std::string& query);
    bool prepare(const std::string& query, sqlite3_stmt** ppStmt);

    bool setObject(Object* obj, Error* err);
    bool getObject(const std::string& objID, Error* err);
    bool deleteObject(const std::string& objID, Error* err);

    bool browse(Query* q, Properties* props, Error* err);
    bool search(Query* q, Properties* props, Error* err);

protected:
    sqlite3* db_;
  };
}
}

#endif
