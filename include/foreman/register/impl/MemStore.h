/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTER_MEMSTORE_H_
#define _FOREMANCC_REGISTER_MEMSTORE_H_

#include <foreman/register/Store.h>
#include <foreman/register/impl/ObjectMap.h>

namespace Foreman {
namespace Register {

  ////////////////////////////////////////////////
  // MemStore
  ////////////////////////////////////////////////

  class MemStore : public Store, public ObjectMap {
public:
    MemStore();
    ~MemStore();

    const char* getVersion();
    const char* getType();

    bool open();
    bool isOpened();
    bool close();
    bool clear();

    bool setObject(Object* obj, Error* err);
    bool getObject(const std::string& objId, Object* obj, Error* err);
    bool removeObject(const std::string& objId, Error* err);
  };
}
}

#endif
