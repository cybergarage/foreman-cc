/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/foreman-c.h>
#include <foreman/registry/Store.h>

using namespace Foreman::Registry;

////////////////////////////////////////////////
// foreman_registry_store_new
////////////////////////////////////////////////

ForemanRegistryStore* foreman_registry_store_new()
{
  return NULL;
  //return new Store();
}

////////////////////////////////////////////////
// foreman_registry_store_delete
////////////////////////////////////////////////

bool foreman_registry_store_delete(ForemanRegistryStore* store)
{
  if (!store)
    return false;
  delete (Store*)store;
  return true;
}
