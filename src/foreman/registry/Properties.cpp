/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/registry/Property.h>

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

////////////////////////////////////////////////
// setProperty
////////////////////////////////////////////////

bool Properties::setProperty(Property* prop)
{
  Property *currProp = getProperty(prop->getName());
  if (currProp) {
    currProp->setData(prop->getData());
    return true;
  }
  
  return addProperty(new Property(prop));
}

////////////////////////////////////////////////
// getProperty
////////////////////////////////////////////////

Property* Properties::getProperty(size_t n)
{
  if ((size() - 1) < n)
    return NULL;
  return at(n).get();
}

////////////////////////////////////////////////
// getProperty
////////////////////////////////////////////////

Property* Properties::getProperty(const std::string& name)
{
  size_t propCont = size();
  for (size_t n = 0; n < propCont; n++) {
    Property* prop = getProperty(n);
    if (!prop)
      continue;
    if (prop->hasName(name))
      return prop;
  }
  return NULL;
}

