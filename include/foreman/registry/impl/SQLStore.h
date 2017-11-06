/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTRY_SQLSTORE_H_
#define _FOREMANCC_REGISTRY_SQLSTORE_H_

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

    char* getVersion();
  };

  ////////////////////////////////////////////////
  // SQLLiteStore
  ////////////////////////////////////////////////

  class SQLLiteStore : public SQLStore {
public:
    SQLLiteStore();
    ~SQLLiteStore();

    const char* getType();

    bool open();
    bool isOpened();
    bool close();

    bool setObject(Object* obj, Error* err);
    bool getObject(const std::string& objID, Error* err);
    bool deleteObject(const std::string& objID, Error* err);

    bool browse(Query* q, Properties* props, Error* err);
    bool search(Query* q, Properties* props, Error* err);
  };
}
}

#endif
