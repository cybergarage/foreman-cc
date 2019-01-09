/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTER_OBJECTMAP_H_
#define _FOREMANCC_REGISTER_OBJECTMAP_H_

#include <map>
#include <memory>

#include <foreman/register/Object.h>

namespace Foreman {
namespace Register {

  ////////////////////////////////////////////////
  // ObjectMap
  ////////////////////////////////////////////////

  class ObjectMap : public std::map<std::string, std::shared_ptr<Object>> {

public:
    ObjectMap();
    ~ObjectMap();

    bool set(const Object* obj);
    bool get(const std::string& key, Object* obj) const;

    bool set(const std::string& key, const std::string& value);
    bool get(const std::string& key, std::string* value) const;

    bool remove(const std::string& key);
  };
}
}

#endif
