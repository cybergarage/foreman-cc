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

////////////////////////////////////////////////
// foreman_registry_query_setid
////////////////////////////////////////////////

bool foreman_registry_object_setid(ForemanRegistryObject* obj, const char* id)
{
  if (!obj)
    return false;
  ((Object*)obj)->setId(id);
  return true;
}

////////////////////////////////////////////////
// foreman_registry_query_getid
////////////////////////////////////////////////

bool foreman_registry_object_getid(ForemanRegistryObject* obj, const char** id)
{
  if (!obj || !id)
    return false;
  *id = ((Object*)obj)->getId();
  return true;
}

////////////////////////////////////////////////
// foreman_registry_query_setparentid
////////////////////////////////////////////////

bool foreman_registry_object_setparentid(ForemanRegistryObject* obj, const char* pid)
{
  if (!obj)
    return false;
  ((Object*)obj)->setParentId(pid);
  return true;
}

////////////////////////////////////////////////
// foreman_registry_query_getparentid
////////////////////////////////////////////////

bool foreman_registry_object_getparentid(ForemanRegistryObject* obj, const char** pid)
{
  if (!obj || !pid)
    return false;
  *pid = ((Object*)obj)->getParentId();
  return true;
}

////////////////////////////////////////////////
// foreman_registry_query_setname
////////////////////////////////////////////////

bool foreman_registry_object_setname(ForemanRegistryObject* obj, const char* name)
{
  if (!obj)
    return false;
  ((Object*)obj)->setName(name);
  return true;
}

////////////////////////////////////////////////
// foreman_registry_object_getname
////////////////////////////////////////////////

bool foreman_registry_object_getname(ForemanRegistryObject* obj, const char** name)
{
  if (!obj || !name)
    return false;
  *name = ((Object*)obj)->getName();
  return true;
}

////////////////////////////////////////////////
// foreman_registry_object_setdata
////////////////////////////////////////////////

bool foreman_registry_object_setdata(ForemanRegistryObject* obj, const char* data)
{
  if (!obj)
    return false;
  ((Object*)obj)->setData(data);
  return true;
}

////////////////////////////////////////////////
// foreman_registry_object_setpropertydata
////////////////////////////////////////////////

bool foreman_registry_object_setpropertydata(ForemanRegistryObject* obj, const char* data)
{
  if (!obj)
    return false;
  ((Object*)obj)->setPropertyData(data);
  return true;
}

////////////////////////////////////////////////
// foreman_registry_object_getdata
////////////////////////////////////////////////

bool foreman_registry_object_getdata(ForemanRegistryObject* obj, const char** data)
{
  if (!obj || !data)
    return false;
  *data = ((Object*)obj)->getData();
  return true;
}

////////////////////////////////////////////////
// foreman_registry_object_getpropertydata
////////////////////////////////////////////////

bool foreman_registry_object_getpropertydata(ForemanRegistryObject* obj, const char** data)
{
  if (!obj || !data)
    return false;
  *data = ((Object*)obj)->getPropertyData();
  return true;
}

////////////////////////////////////////////////
// foreman_registry_object_setproperty
////////////////////////////////////////////////

bool foreman_registry_object_setproperty(ForemanRegistryObject* obj, ForemanRegistryProperty* prop)
{
  if (!obj || !prop)
    return false;
  return ((Object*)obj)->setProperty(((Property*)prop));
}

////////////////////////////////////////////////
// foreman_registry_object_getproperties
////////////////////////////////////////////////

bool foreman_registry_object_getproperties(ForemanRegistryObject* obj, ForemanRegistryProperties* props)
{
  if (!obj || !props)
    return false;
  return ((Object*)obj)->getProperties(((Properties*)props));
}
