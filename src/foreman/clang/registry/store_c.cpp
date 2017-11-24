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

const char* foreman_registry_store_gettype(ForemanRegistryStore* store);

////////////////////////////////////////////////
// foreman_registry_store_open
////////////////////////////////////////////////
const char* foreman_registry_store_getversion(ForemanRegistryStore* store);

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

////////////////////////////////////////////////
// foreman_registry_store_clear
////////////////////////////////////////////////

bool foreman_registry_store_clear(ForemanRegistryStore* store)
{
  if (!store)
    return false;
  return ((Foreman::Registry::Store*)(store))->clear();
}

////////////////////////////////////////////////
// foreman_registry_store_gettype
////////////////////////////////////////////////

const char* foreman_registry_store_gettype(ForemanRegistryStore* store)
{
  if (!store)
    return "";
  return ((Foreman::Registry::Store*)(store))->getType();
}

////////////////////////////////////////////////
// foreman_registry_store_getversion
////////////////////////////////////////////////

const char* foreman_registry_store_getversion(ForemanRegistryStore* store)
{
  if (!store)
    return "";
  return ((Foreman::Registry::Store*)(store))->getVersion();
}

////////////////////////////////////////////////
// foreman_registry_store_createobject
////////////////////////////////////////////////

bool foreman_registry_store_createobject(ForemanRegistryStore* store, ForemanRegistryObject* obj, ForemanError* err)
{
  if (!store)
    return false;
  return ((Foreman::Registry::Store*)(store))->createObject((Foreman::Registry::Object*)(obj), (Foreman::Error*)(err));
}

////////////////////////////////////////////////
// foreman_registry_store_updateobject
////////////////////////////////////////////////

bool foreman_registry_store_updateobject(ForemanRegistryStore* store, ForemanRegistryObject* obj, ForemanError* err)
{
  if (!store)
    return false;
  return ((Foreman::Registry::Store*)(store))->updateObject((Foreman::Registry::Object*)(obj), (Foreman::Error*)(err));
}

////////////////////////////////////////////////
// foreman_registry_store_getobject
////////////////////////////////////////////////

bool foreman_registry_store_getobject(ForemanRegistryStore* store, const char* objId, ForemanRegistryObject* obj, ForemanError* err)
{
  if (!store)
    return false;
  return ((Foreman::Registry::Store*)(store))->getObject(objId, (Foreman::Registry::Object*)(obj), (Foreman::Error*)(err));
}

////////////////////////////////////////////////
// foreman_registry_store_deleteobject
////////////////////////////////////////////////

bool foreman_registry_store_deleteobject(ForemanRegistryStore* store, const char* objId, ForemanError* err)
{
  if (!store)
    return false;
  return ((Foreman::Registry::Store*)(store))->deleteObject(objId, (Foreman::Error*)(err));
}

////////////////////////////////////////////////
// foreman_registry_store_browse
////////////////////////////////////////////////

bool foreman_registry_store_browse(ForemanRegistryStore* store, ForemanRegistryQuery* q, ForemanRegistryObjects* objs, ForemanError* err)
{
  if (!store)
    return false;
  return ((Foreman::Registry::Store*)(store))->browse((Foreman::Registry::Query*)(q), (Foreman::Registry::Objects*)(objs), (Foreman::Error*)(err));
}

////////////////////////////////////////////////
// foreman_registry_store_search
////////////////////////////////////////////////

bool foreman_registry_store_search(ForemanRegistryStore* store, ForemanRegistryQuery* q, ForemanRegistryObjects* objs, ForemanError* err)
{
  if (!store)
    return false;
  return ((Foreman::Registry::Store*)(store))->search((Foreman::Registry::Query*)(q), (Foreman::Registry::Objects*)(objs), (Foreman::Error*)(err));
}
