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
#include <string>

namespace Foreman {
namespace Registry {

  ////////////////////////////////////////////////
  // Query
  ////////////////////////////////////////////////

  class Query {
public:
    Query();
    virtual ~Query();

    void setParentId(const std::string& value)
    {
      this->parentId = value;
    }

    const char* getParentId() const
    {
      return this->parentId.c_str();
    }

    bool hasParentId() const
    {
      return (0 < this->parentId.length()) ? true : false;
    }

public:
    std::string parentId;
  };
}
}

#endif
