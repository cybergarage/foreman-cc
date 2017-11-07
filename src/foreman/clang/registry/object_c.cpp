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
#include <foreman/registry/Object.h>

using namespace Foreman::Registry;

////////////////////////////////////////////////
// foreman_registry_object_new
////////////////////////////////////////////////

ForemanRegistryObject* foreman_registry_object_new()
{
  return new Object();
}

////////////////////////////////////////////////
// foreman_registry_object_delete
////////////////////////////////////////////////

bool foreman_registry_object_delete(ForemanRegistryObject* obj)
{
  if (!obj)
    return false;
  delete (Object*)obj;
  return true;
}
