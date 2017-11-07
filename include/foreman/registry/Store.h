/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTRY_STORE_H_
#define _FOREMANCC_REGISTRY_STORE_H_

#include <foreman/common/Error.h>
#include <foreman/registry/Object.h>
#include <foreman/registry/Query.h>

namespace Foreman {
namespace Registry {

  ////////////////////////////////////////////////
  // Store
  ////////////////////////////////////////////////

  class Store {
public:
    Store();
    virtual ~Store();

    virtual const char* getType() = 0;
    virtual const char* getVersion() = 0;

    virtual bool open() = 0;
    virtual bool isOpened() = 0;
    virtual bool close() = 0;

    virtual bool setObject(Object* obj, Error* err) = 0;
    virtual bool getObject(const std::string& objID, Error* err) = 0;
    virtual bool deleteObject(const std::string& objID, Error* err) = 0;

    virtual bool browse(Query* q, Properties* props, Error* err) = 0;
    virtual bool search(Query* q, Properties* props, Error* err) = 0;
  };
}
}

#endif
