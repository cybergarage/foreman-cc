/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/register/Object.h>
#include <foreman/register/register-c.h>

using namespace Foreman::Register;

////////////////////////////////////////////////
// foreman_register_object_new
////////////////////////////////////////////////

ForemanRegisterObject* foreman_register_object_new()
{
  return new Object();
}

////////////////////////////////////////////////
// foreman_register_object_delete
////////////////////////////////////////////////

bool foreman_register_object_delete(ForemanRegisterObject* obj)
{
  if (!obj)
    return false;
  delete (Object*)obj;
  return true;
}

////////////////////////////////////////////////
// foreman_register_object_setkey
////////////////////////////////////////////////

bool foreman_register_object_setkey(ForemanRegisterObject* obj, const char* key)
{
  if (!obj)
    return false;
  ((Object*)obj)->setKey(key);
  return true;
}

////////////////////////////////////////////////
// foreman_register_object_getkey
////////////////////////////////////////////////

bool foreman_register_object_getkey(ForemanRegisterObject* obj, const char** key)
{
  if (!obj || !key)
    return false;
  *key = ((Object*)obj)->getKey();
  return true;
}

////////////////////////////////////////////////
// foreman_register_object_setdata
////////////////////////////////////////////////

bool foreman_register_object_setdata(ForemanRegisterObject* obj, const char* data)
{
  if (!obj)
    return false;
  ((Object*)obj)->setData(data);
  return true;
}

////////////////////////////////////////////////
// foreman_register_object_getdata
////////////////////////////////////////////////

bool foreman_register_object_getdata(ForemanRegisterObject* obj, const char** data)
{
  if (!obj || !data)
    return false;
  *data = ((Object*)obj)->getData();
  return true;
}

////////////////////////////////////////////////
// foreman_register_object_getversion
////////////////////////////////////////////////

bool foreman_register_object_getversion(ForemanRegisterObject* obj, long* ver)
{
  if (!obj || !ver)
    return false;
  *ver = ((Object*)obj)->getVersion();
  return true;
}

////////////////////////////////////////////////
// foreman_register_object_gettimestamp
////////////////////////////////////////////////

bool foreman_register_object_gettimestamp(ForemanRegisterObject* obj, time_t* ts)
{
  if (!obj || !ts)
    return false;
  *ts = ((Object*)obj)->getTimestamp();
  return true;
}
