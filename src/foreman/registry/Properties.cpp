/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/registry/Property.h>
#include <foreman/util/Util.h>

using namespace Foreman::Registry;

////////////////////////////////////////////////
// Properties
////////////////////////////////////////////////

Properties::Properties()
{
}

Properties::~Properties() {}

////////////////////////////////////////////////
// addProperties
////////////////////////////////////////////////

bool Properties::addProperty(Property* prop)
{
  return addProperty(std::shared_ptr<Foreman::Registry::Property>(prop));
}

////////////////////////////////////////////////
// addProperties
////////////////////////////////////////////////

bool Properties::addProperty(const Property& prop)
{
  return addProperty(new Foreman::Registry::Property(prop));
}

////////////////////////////////////////////////
// addProperties
////////////////////////////////////////////////

bool Properties::addProperty(std::shared_ptr<Foreman::Registry::Property> prop)
{
  push_back(prop);
  return true;
}
