/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/Parameter.h>
#include <foreman/action/action-c.h>

using namespace Foreman::Action;

////////////////////////////////////////////////
// foreman_action_parameter_<type>_new
////////////////////////////////////////////////

ForemanActionParameter* foreman_action_parameter_integer_new()
{
  return new Integer();
}

ForemanActionParameter* foreman_action_parameter_real_new()
{
  return new Real();
}

ForemanActionParameter* foreman_action_parameter_bool_new()
{
  return new Bool();
}

ForemanActionParameter* foreman_action_parameter_string_new()
{
  return new String();
}

////////////////////////////////////////////////
// foreman_action_parameter_delete
////////////////////////////////////////////////

bool foreman_action_parameter_delete(ForemanActionParameter* param)
{
  if (!param)
    return false;
  delete (Parameter*)param;
  return true;
}

////////////////////////////////////////////////
// foreman_registry_query_setname
////////////////////////////////////////////////

bool foreman_action_parameter_setname(ForemanActionParameter* param, const char* name)
{
  if (!param)
    return false;
  ((Parameter*)param)->setName(name);
  return true;
}

////////////////////////////////////////////////
// foreman_action_parameter_getname
////////////////////////////////////////////////

const char* foreman_action_parameter_getname(ForemanActionParameter* param)
{
  if (!param)
    return nullptr;
  return ((Parameter*)param)->getName();
}

////////////////////////////////////////////////
// foreman_action_parameter_is<type>
////////////////////////////////////////////////

bool foreman_action_parameter_isinteger(ForemanActionParameter* param)
{
  return ((Parameter*)param)->isInteger();
}

bool foreman_action_parameter_isreal(ForemanActionParameter* param)
{
  return ((Parameter*)param)->isReal();
}

bool foreman_action_parameter_isbool(ForemanActionParameter* param)
{
  return ((Parameter*)param)->isBool();
}

bool foreman_action_parameter_isstring(ForemanActionParameter* param)
{
  return ((Parameter*)param)->isString();
}

////////////////////////////////////////////////
// foreman_action_parameter_set<type>
////////////////////////////////////////////////

bool foreman_action_parameter_setinteger(ForemanActionParameter* param, long value)
{
  auto paramObj = dynamic_cast<Integer*>((Parameter*)param);
  if (!paramObj)
    return false;
  paramObj->setValue(value);
  return true;
}

bool foreman_action_parameter_setreal(ForemanActionParameter* param, double value)
{
  auto paramObj = dynamic_cast<Real*>((Parameter*)param);
  if (!paramObj)
    return false;
  paramObj->setValue(value);
  return true;
}

bool foreman_action_parameter_setbool(ForemanActionParameter* param, bool value)
{
  auto paramObj = dynamic_cast<Bool*>((Parameter*)param);
  if (!paramObj)
    return false;
  paramObj->setValue(value);
  return true;
}

bool foreman_action_parameter_setstring(ForemanActionParameter* param, const char* value)
{
  auto paramObj = dynamic_cast<String*>((Parameter*)param);
  if (!paramObj)
    return false;
  paramObj->setValue(value);
  return true;
}

////////////////////////////////////////////////
// foreman_action_parameter_get<type>
////////////////////////////////////////////////

long foreman_action_parameter_getinteger(ForemanActionParameter* param)
{
  auto paramObj = dynamic_cast<Integer*>((Parameter*)param);
  if (!paramObj)
    return 0;
  return paramObj->getValue();
}

double foreman_action_parameter_getreal(ForemanActionParameter* param)
{
  auto paramObj = dynamic_cast<Real*>((Parameter*)param);
  if (!paramObj)
    return 0.0;
  return paramObj->getValue();
}

bool foreman_action_parameter_getbool(ForemanActionParameter* param)
{
  auto paramObj = dynamic_cast<Bool*>((Parameter*)param);
  if (!paramObj)
    return false;
  return paramObj->getValue();
}

const char* foreman_action_parameter_getstring(ForemanActionParameter* param)
{
  auto paramObj = dynamic_cast<String*>((Parameter*)param);
  if (!paramObj)
    return nullptr;
  return paramObj->getValue().c_str();
}
