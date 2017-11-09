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
#include <foreman/registry/impl/StoreImpl.h>

using namespace Foreman::Registry;

////////////////////////////////////////////////
// foreman_registry_sqlite_store_new
////////////////////////////////////////////////

ForemanRegistryStore* foreman_registry_sqlite_store_new()
{
  return new SQLiteStore();
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

////////////////////////////////////////////////
// foreman_registry_store_open
////////////////////////////////////////////////

bool foreman_registry_store_open(ForemanRegistryStore* store)
{
  if (!store)
    return false;
  return ((Foreman::Registry::Store*)(store))->open();
}

////////////////////////////////////////////////
// foreman_registry_store_close
////////////////////////////////////////////////

bool foreman_registry_store_close(ForemanRegistryStore* store)
{
  if (!store)
    return false;
  return ((Foreman::Registry::Store*)(store))->close();
}
