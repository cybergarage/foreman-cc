/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/registry/Object.h>

using namespace Foreman::Registry;

////////////////////////////////////////////////
// Objects
////////////////////////////////////////////////

Objects::Objects()
{
}

Objects::~Objects() {}

////////////////////////////////////////////////
// addObjects
////////////////////////////////////////////////

bool Objects::addObject(Object* prop)
{
  return addObject(std::shared_ptr<Foreman::Registry::Object>(prop));
}

////////////////////////////////////////////////
// addObjects
////////////////////////////////////////////////

bool Objects::addObject(const Object& prop)
{
  return addObject(new Foreman::Registry::Object(prop));
}

////////////////////////////////////////////////
// addObjects
////////////////////////////////////////////////

bool Objects::addObject(std::shared_ptr<Foreman::Registry::Object> prop)
{
  push_back(prop);
  return true;
}

////////////////////////////////////////////////
// getObject
////////////////////////////////////////////////

Object* Objects::getObject(size_t n)
{
  if ((size() - 1) < n)
    return NULL;
  return at(n).get();
}
