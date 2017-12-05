/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/registry/Object.h>
#include <foreman/registry/registry-c.h>

using namespace Foreman::Registry;

////////////////////////////////////////////////
// foreman_registry_objects_new
////////////////////////////////////////////////

ForemanRegistryObjects* foreman_registry_objects_new()
{
  return new Objects();
}

////////////////////////////////////////////////
// foreman_registry_objects_delete
////////////////////////////////////////////////

bool foreman_registry_objects_delete(ForemanRegistryObjects* objs)
{
  if (!objs)
    return false;
  delete (Objects*)objs;
  return true;
}

////////////////////////////////////////////////
// foreman_registry_objects_size
////////////////////////////////////////////////

size_t foreman_registry_objects_size(ForemanRegistryObjects* objs)
{
  if (!objs)
    return 0;
  return ((Objects*)objs)->size();
}

////////////////////////////////////////////////
// foreman_registry_objects_addobject
////////////////////////////////////////////////

bool foreman_registry_objects_addobject(ForemanRegistryObjects* objs, ForemanRegistryObject* obj)
{
  if (!objs)
    return false;
  return ((Objects*)objs)->addObject((Object*)obj);
}

////////////////////////////////////////////////
// foreman_registry_objects_getobject
////////////////////////////////////////////////

ForemanRegistryObject* foreman_registry_objects_getobject(ForemanRegistryObjects* objs, size_t n)
{
  if (!objs)
    return NULL;
  return ((Objects*)objs)->getObject(n);
}
