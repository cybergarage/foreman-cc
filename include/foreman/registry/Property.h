/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTRY_PROPERTY_H_
#define _FOREMANCC_REGISTRY_PROPERTY_H_

#include <string>

namespace Foreman {
namespace Registry {

  ////////////////////////////////////////////////
  // Property
  ////////////////////////////////////////////////

  class Property {

public:
    Property();

    virtual ~Property();

    void setName(const std::string& value)
    {
      this->name = value;
    }

    const char* getName() const
    {
      return this->name.c_str();
    }

    void setValue(const std::string& value)
    {
      this->value = value;
    }

    const char* getValue() const
    {
      return this->value.c_str();
    }

private:
    void initialize();

    std::string name;
    std::string value;
  };
}
}

#endif
