/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTRY_OBJECT_H_
#define _FOREMANCC_REGISTRY_OBJECT_H_

#include <foreman/registry/Object.h>
#include <string>
#include <vector>

namespace Foreman {
namespace Registry {

  ////////////////////////////////////////////////
  // Object
  ////////////////////////////////////////////////

  class Object {

public:
    Object();

    virtual ~Object();

    void setId(const std::string& value)
    {
      this->objId = value;
    }

    const char* getId() const
    {
      return this->objId.c_str();
    }

    void setParentId(const std::string& value)
    {
      this->parentId = value;
    }

    const char* getParentId() const
    {
      return this->parentId.c_str();
    }

    void setName(const std::string& value)
    {
      this->name = value;
    }

    const char* getName() const
    {
      return this->name.c_str();
    }

    void setData(const std::string& value)
    {
      this->data = value;
    }

    const char* getData() const
    {
      return this->data.c_str();
    }

public:
    void initialize();

    std::string objId;
    std::string parentId;
    std::string name;
    std::string data;
  };

  ////////////////////////////////////////////////
  // Objects
  ////////////////////////////////////////////////

  class Objects : public std::vector<std::shared_ptr<Object>> {
public:
    Objects();
    virtual ~Objects();

    bool addObject(Object* prop);
    bool addObject(const Object& prop);
    bool addObject(std::shared_ptr<Foreman::Registry::Object> prop);

    Object* getObject(size_t n)
    {
      return at(n).get();
    }
  };
}
}

#endif
