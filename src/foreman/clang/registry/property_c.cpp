/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/registry/registry-c.h>
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

////////////////////////////////////////////////
// foreman_registry_query_setname
////////////////////////////////////////////////

bool foreman_registry_property_setname(ForemanRegistryProperty* prop, const char* name)
{
  if (!prop)
    return false;
  ((Property*)prop)->setName(name);
  return true;
}

////////////////////////////////////////////////
// foreman_registry_property_getname
////////////////////////////////////////////////

bool foreman_registry_property_getname(ForemanRegistryProperty* prop, const char** name)
{
  if (!prop || !name)
    return false;
  *name = ((Property*)prop)->getName();
  return true;
}

////////////////////////////////////////////////
// foreman_registry_property_setdata
////////////////////////////////////////////////

bool foreman_registry_property_setdata(ForemanRegistryProperty* prop, const char* pid)
{
  if (!prop)
    return false;
  ((Property*)prop)->setData(pid);
  return true;
}

////////////////////////////////////////////////
// foreman_registry_property_getdata
////////////////////////////////////////////////

bool foreman_registry_property_getdata(ForemanRegistryProperty* prop, const char** data)
{
  if (!prop || !data)
    return false;
  *data = ((Property*)prop)->getData();
  return true;
}
