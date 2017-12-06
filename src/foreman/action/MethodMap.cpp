/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/Method.h>

////////////////////////////////////////////////
// MethodMap
////////////////////////////////////////////////

Foreman::Action::MethodMap::MethodMap()
{
}

Foreman::Action::MethodMap::~MethodMap()
{
  clear();
}

////////////////////////////////////////////////
// hasMethod
////////////////////////////////////////////////

bool Foreman::Action::MethodMap::hasMethod(const std::string& name) const
{
  return (find(name) != end()) ? true : false;
}

////////////////////////////////////////////////
// getMethod
////////////////////////////////////////////////

Foreman::Action::Method* Foreman::Action::MethodMap::getMethod(const std::string& name)
{
  auto methodIt = find(name);
  if (methodIt == end())
    return NULL;
  return methodIt->second;
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

void Foreman::Action::MethodMap::clear()
{
  for (auto methodIt = begin(); methodIt != end(); methodIt++) {
    Method* script = methodIt->second;
    if (script) {
      delete script;
    }
  }
  std::map<std::string, Method*>::clear();
}
