/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTRY_PROPERTY_H_
#define _FOREMANCC_REGISTRY_PROPERTY_H_

#include <string>
#include <vector>

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

    bool hasName(const std::string& value)
    {
      return (this->name.compare(value) == 0) ? true : false;
    }

    void setData(const std::string& value)
    {
      this->data = value;
    }

    const char* getData() const
    {
      return this->data.c_str();
    }

private:
    void initialize();

    std::string name;
    std::string data;
  };

  ////////////////////////////////////////////////
  // Properties
  ////////////////////////////////////////////////

  class Properties : public std::vector<std::shared_ptr<Property>> {
public:
    Properties();
    virtual ~Properties();

    bool addProperty(Property* prop);
    bool addProperty(const Property& prop);
    bool addProperty(std::shared_ptr<Foreman::Registry::Property> prop);

    bool setProperty(Property* prop);

    Property* getProperty(size_t n);
    Property* getProperty(const std::string& name);
  };
}
}

#endif
