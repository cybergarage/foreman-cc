/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Const.h>
#include <foreman/register/impl/ObjectMap.h>

using namespace Foreman::Register;

ObjectMap::ObjectMap()
{
}

ObjectMap::~ObjectMap()
{
}

bool ObjectMap::set(const Object* obj)
{
  if (!obj) {
    return false;
  }

  std::shared_ptr<Object> newObj(new Object(obj));

  auto key = obj->getKey();
  auto valueIt = find(key);
  if (valueIt != end()) {
    auto currObj = *(valueIt->second);
    newObj->setVersion(currObj.getVersion() + 1);
    valueIt->second = newObj;
    return true;
  }

  insert(std::pair<std::string, std::shared_ptr<Object>>(key, newObj));

  return true;
}

bool ObjectMap::get(const std::string& key, Object* obj) const
{
  if (!obj) {
    return false;
  }

  auto valueIt = find(key);
  if (valueIt == end())
    return false;

  obj->set(valueIt->second.get());

  return true;
}

bool ObjectMap::set(const std::string& key, const std::string& value)
{
  Object obj;
  obj.setKey(key);
  obj.setData(value);
  return set(&obj);
}

bool ObjectMap::get(const std::string& key, std::string* value) const
{
  Object obj;
  if (!get(key, &obj))
    return false;
  *value = obj.getData();
  return true;
}

bool ObjectMap::remove(const std::string& key)
{
  return (0 < erase(key)) ? true : false;
}
