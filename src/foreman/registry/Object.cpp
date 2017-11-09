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
// Object
////////////////////////////////////////////////

Object::Object()
{
}

Object::~Object()
{
}

////////////////////////////////////////////////
// equals
////////////////////////////////////////////////

bool Object::equals(Object* obj) const
{
  if (this->objId.compare(obj->getId()) != 0)
    return false;

  if (this->parentId.compare(obj->getParentId()) != 0)
    return false;

  if (this->name.compare(obj->getName()) != 0)
    return false;

  if (this->data.compare(obj->getData()) != 0)
    return false;

  return true;
}
