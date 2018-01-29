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
// foreman_action_parameters_new
////////////////////////////////////////////////

ForemanActionParameters* foreman_action_parameters_new()
{
  return new Parameters();
}

////////////////////////////////////////////////
// foreman_action_parameters_delete
////////////////////////////////////////////////

bool foreman_action_parameters_delete(ForemanActionParameters* params)
{
  if (!params)
    return false;
  delete (Parameters*)params;
  return true;
}

////////////////////////////////////////////////
// foreman_action_parameters_size
////////////////////////////////////////////////

size_t foreman_action_parameters_size(ForemanActionParameters* params)
{
  if (!params)
    return 0;
  return ((Parameters*)params)->size();
}

////////////////////////////////////////////////
// foreman_action_parameters_addparameter
////////////////////////////////////////////////

bool foreman_action_parameters_addparameter(ForemanActionParameters* params, ForemanActionParameter* param)
{
  if (!params || !params)
    return false;
  return ((Parameters*)params)->addParameter((Parameter*)param);
}

////////////////////////////////////////////////
// foreman_action_parameters_getparameter
////////////////////////////////////////////////

ForemanActionParameter* foreman_action_parameters_getparameter(ForemanActionParameters* params, size_t n)
{
  if (!params)
    return NULL;
  return ((Parameters*)params)->getParameter(n);
}
