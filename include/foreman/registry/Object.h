/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTRY_OBJECT_H_
#define _FOREMANCC_REGISTRY_OBJECT_H_

#include <foreman/registry/Property.h>
#include <string>

namespace Foreman {
namespace Registry {

  ////////////////////////////////////////////////
  // Object
  ////////////////////////////////////////////////

  class Object {

public:
    Object();

    virtual ~Object();

    void setName(const std::string& value)
    {
      this->name = value;
    }

    const char* getName() const
    {
      return this->name.c_str();
    }

private:
    void initialize();

    std::string name;
  };
}
}

#endif
