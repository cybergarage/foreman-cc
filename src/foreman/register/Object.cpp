/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <iostream>
#include <sstream>
#include <string>

#include <foreman/register/Object.h>

using namespace Foreman::Register;

////////////////////////////////////////////////
// Object
////////////////////////////////////////////////

Object::Object()
{
  clear();
}

Object::~Object()
{
  clear();
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool Object::clear()
{
  this->key = "";
  this->data = "";
  this->timestamp = 0;
  this->version = 0;

  return true;
}

////////////////////////////////////////////////
// setData
////////////////////////////////////////////////

void Object::setData(const std::string& value)
{
  this->data = value;
  this->version++;
  this->timestamp = time(NULL);
}

////////////////////////////////////////////////
// equals
////////////////////////////////////////////////

bool Object::equals(Object* obj) const
{
  if (this->key.compare(obj->getKey()) != 0)
    return false;

  if (this->data.compare(obj->getData()) != 0)
    return false;

  return true;
}
