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

#include <foreman/register/Object.h>
#include <map>

namespace Foreman {
namespace Register {

  ////////////////////////////////////////////////
  // ObjectMap
  ////////////////////////////////////////////////

  class ObjectMap : public std::map<std::string, Object> {

public:
    ObjectMap();
    ~ObjectMap();

    bool set(const Object reg);
    bool get(const std::string& key, Object* reg) const;

    bool set(const std::string& key, const std::string& value);
    bool get(const std::string& key, std::string* value) const;

    bool remove(const std::string& key);
  };
}
}

#endif
