/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/register/impl/MemStore.h>
#include <foreman/register/register-c.h>

using namespace Foreman::Register;

////////////////////////////////////////////////
// foreman_register_store_new
////////////////////////////////////////////////

ForemanRegisterStore* foreman_register_store_new()
{
  return new MemStore();
}

////////////////////////////////////////////////
// foreman_register_store_delete
////////////////////////////////////////////////

bool foreman_register_store_delete(ForemanRegisterStore* store)
{
  if (!store)
    return false;
  delete (Store*)store;
  return true;
}

////////////////////////////////////////////////
// foreman_register_store_open
////////////////////////////////////////////////

const char* foreman_register_store_gettype(ForemanRegisterStore* store);

////////////////////////////////////////////////
// foreman_register_store_open
////////////////////////////////////////////////
const char* foreman_register_store_getversion(ForemanRegisterStore* store);

////////////////////////////////////////////////
// foreman_register_store_open
////////////////////////////////////////////////

bool foreman_register_store_open(ForemanRegisterStore* store)
{
  if (!store)
    return false;
  return ((Foreman::Register::Store*)(store))->open();
}

////////////////////////////////////////////////
// foreman_register_store_close
////////////////////////////////////////////////

bool foreman_register_store_close(ForemanRegisterStore* store)
{
  if (!store)
    return false;
  return ((Foreman::Register::Store*)(store))->close();
}

////////////////////////////////////////////////
// foreman_register_store_clear
////////////////////////////////////////////////

bool foreman_register_store_clear(ForemanRegisterStore* store)
{
  if (!store)
    return false;
  return ((Foreman::Register::Store*)(store))->clear();
}

////////////////////////////////////////////////
// foreman_register_store_gettype
////////////////////////////////////////////////

const char* foreman_register_store_gettype(ForemanRegisterStore* store)
{
  if (!store)
    return "";
  return ((Foreman::Register::Store*)(store))->getType();
}

////////////////////////////////////////////////
// foreman_register_store_getversion
////////////////////////////////////////////////

const char* foreman_register_store_getversion(ForemanRegisterStore* store)
{
  if (!store)
    return "";
  return ((Foreman::Register::Store*)(store))->getVersion();
}

////////////////////////////////////////////////
// foreman_register_store_setobject
////////////////////////////////////////////////

bool foreman_register_store_setobject(ForemanRegisterStore* store, ForemanRegisterObject* obj, ForemanError* err)
{
  if (!store)
    return false;
  return ((Foreman::Register::Store*)(store))->setObject((Foreman::Register::Object*)(obj), (Foreman::Error*)(err));
}

////////////////////////////////////////////////
// foreman_register_store_getobject
////////////////////////////////////////////////

bool foreman_register_store_getobject(ForemanRegisterStore* store, const char* objId, ForemanRegisterObject* obj, ForemanError* err)
{
  if (!store)
    return false;
  return ((Foreman::Register::Store*)(store))->getObject(objId, (Foreman::Register::Object*)(obj), (Foreman::Error*)(err));
}

////////////////////////////////////////////////
// foreman_register_store_removeobject
////////////////////////////////////////////////

bool foreman_register_store_removeobject(ForemanRegisterStore* store, const char* objId, ForemanError* err)
{
  if (!store)
    return false;
  return ((Foreman::Register::Store*)(store))->removeObject(objId, (Foreman::Error*)(err));
}
