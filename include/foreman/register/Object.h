/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTER_OBJECT_H_
#define _FOREMANCC_REGISTER_OBJECT_H_

#include <string>
#include <time.h>

namespace Foreman {
namespace Register {

  ////////////////////////////////////////////////
  // Object
  ////////////////////////////////////////////////

  class Object {

public:
    Object();
    Object(const Object* other);

    virtual ~Object();

    void set(const Object* other);

    void setKey(const std::string& value)
    {
      this->key = value;
    }

    const char* getKey() const
    {
      return this->key.c_str();
    }

    bool hasKey() const
    {
      return (0 < this->key.length()) ? true : false;
    }

    void setData(const std::string& value);

    const char* getData() const
    {
      return this->data.c_str();
    }

    bool hasData() const
    {
      return (0 < this->data.length()) ? true : false;
    }

    void setVersion(int ver)
    {
      this->version = ver;
    }

    int getVersion()
    {
      return this->version;
    }

    time_t getTimestamp()
    {
      return this->timestamp;
    }

    bool equals(Object* obj) const;

    bool clear();

private:
    std::string key;
    std::string data;
    int version;
    time_t timestamp;
  };
}
}

#endif
