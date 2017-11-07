/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTRY_QUERY_H_
#define _FOREMANCC_REGISTRY_QUERY_H_

#include <foreman/Platform.h>

namespace Foreman {
namespace Registry {

  ////////////////////////////////////////////////
  // Query
  ////////////////////////////////////////////////

  class Query {
public:
    Query();
    virtual ~Query();
  };
}
}

#endif
