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
// Property
////////////////////////////////////////////////

Property::Property()
{
}

Property::~Property()
{
}

Property::Property(const Property* prop)
{
  setProperty(prop);
}

////////////////////////////////////////////////
// Property
////////////////////////////////////////////////

void Property::setProperty(const Property* prop)
{
  setName(prop->getName());
  setData(prop->getData());
}
