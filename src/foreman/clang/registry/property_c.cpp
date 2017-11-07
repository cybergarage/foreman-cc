/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/foreman-c.h>
#include <foreman/registry/Property.h>

using namespace Foreman::Registry;

////////////////////////////////////////////////
// foreman_registry_property_new
////////////////////////////////////////////////

ForemanRegistryProperty* foreman_registry_property_new()
{
  return new Property();
}

////////////////////////////////////////////////
// foreman_registry_property_delete
////////////////////////////////////////////////

bool foreman_registry_property_delete(ForemanRegistryProperty* prop)
{
  if (!prop)
    return false;
  delete (Property*)prop;
  return true;
}
