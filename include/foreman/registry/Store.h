/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
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

    virtual bool open() = 0;
    virtual bool isOpened() = 0;
    virtual bool close() = 0;
  };
}
}

#endif
