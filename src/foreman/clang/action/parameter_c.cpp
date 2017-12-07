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

bool foreman_action_parameter_getname(ForemanActionParameter* param, const char** name)
{
  if (!param || !name)
    return false;
  *name = ((Parameter*)param)->getName();
  return true;
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

bool foreman_action_parameter_getinteger(ForemanActionParameter* param, long *value)
{
  auto paramObj = dynamic_cast<Integer*>((Parameter*)param);
  if (!paramObj)
    return false;
  *value = paramObj->getValue();
  return true;
}

bool foreman_action_parameter_getreal(ForemanActionParameter* param, double *value)
{
  auto paramObj = dynamic_cast<Real*>((Parameter*)param);
  if (!paramObj)
    return false;
  *value = paramObj->getValue();
  return true;
}

bool foreman_action_parameter_getbool(ForemanActionParameter* param, bool *value)
{
  auto paramObj = dynamic_cast<Bool*>((Parameter*)param);
  if (!paramObj)
    return false;
  *value = paramObj->getValue();
  return true;
}

bool foreman_action_parameter_getstring(ForemanActionParameter* param, const char ** value)
{
  auto paramObj = dynamic_cast<String*>((Parameter*)param);
  if (!paramObj)
    return false;
  *value = paramObj->getValue().c_str();
  return true;
}
