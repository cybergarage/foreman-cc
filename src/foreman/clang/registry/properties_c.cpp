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
// foreman_registry_properties_new
////////////////////////////////////////////////

ForemanRegistryProperties* foreman_registry_properties_new()
{
  return new Properties();
}

////////////////////////////////////////////////
// foreman_registry_properties_delete
////////////////////////////////////////////////

bool foreman_registry_properties_delete(ForemanRegistryProperties* props)
{
  if (!props)
    return false;
  delete (Properties*)props;
  return true;
}

////////////////////////////////////////////////
// foreman_registry_properties_size
////////////////////////////////////////////////

size_t foreman_registry_properties_size(ForemanRegistryProperties* props)
{
  if (!props)
    return 0;
  return ((Properties*)props)->size();
}

////////////////////////////////////////////////
// foreman_registry_properties_addproperty
////////////////////////////////////////////////

bool foreman_registry_properties_addproperty(ForemanRegistryProperties* props, ForemanRegistryProperty* prop)
{
  if (!props || !prop)
    return false;
  return ((Properties*)props)->addProperty((Property*)prop);
}

////////////////////////////////////////////////
// foreman_registry_properties_getproperty
////////////////////////////////////////////////

ForemanRegistryProperty* foreman_registry_properties_getproperty(ForemanRegistryProperties* props, size_t n)
{
  if (!props)
    return NULL;
  return ((Properties*)props)->getProperty(n);
}
