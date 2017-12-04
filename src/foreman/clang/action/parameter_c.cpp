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
#include <foreman/foreman-c.h>

using namespace Foreman::Action;

////////////////////////////////////////////////
// foreman_action_parameter_new
////////////////////////////////////////////////

ForemanActionParameter* foreman_action_parameter_new()
{
  return NULL;
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
