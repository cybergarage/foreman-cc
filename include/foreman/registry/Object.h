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

#include <string>
#include <vector>

#include <foreman/Const.h>
#include <foreman/registry/Object.h>

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

    bool hasId() const
    {
      return (0 < this->objId.length()) ? true : false;
    }

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

    bool isRootParentId() const
    {
      return (this->parentId.compare(FOREMANCC_REGISTRY_ROOT_OBJECT_ID) == 0) ? true : false;
    }

    void setName(const std::string& value)
    {
      this->name = value;
    }

    const char* getName() const
    {
      return this->name.c_str();
    }

    bool hasName() const
    {
      return (0 < this->name.length()) ? true : false;
    }

    void setData(const std::string& value)
    {
      this->data = value;
    }

    const char* getData() const
    {
      return this->data.c_str();
    }

    bool hasData() const
    {
      return (0 < this->data.length()) ? true : false;
    }

    bool equals(Object* obj) const;

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

    bool addObject(Object* obj);
    bool addObject(const Object& obj);
    bool addObject(std::shared_ptr<Foreman::Registry::Object> obj);

    Object* getObject(size_t n)
    {
      return at(n).get();
    }
  };
}
}

#endif
