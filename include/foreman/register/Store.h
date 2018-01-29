/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTER_STORE_H_
#define _FOREMANCC_REGISTER_STORE_H_

#include <foreman/common/Error.h>
#include <foreman/register/Object.h>

namespace Foreman {
namespace Register {

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
    virtual bool close() = 0;
    virtual bool clear() = 0;

    virtual bool setObject(Object* obj, Error* err) = 0;
    virtual bool getObject(const std::string& objId, Object* obj, Error* err) = 0;
    virtual bool removeObject(const std::string& objId, Error* err) = 0;

    virtual size_t size() = 0;
};
}
}

#endif
