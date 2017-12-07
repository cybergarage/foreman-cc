/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/Method.h>
#include <foreman/action/action-c.h>
#include <foreman/action/impl/ManagerImpl.h>

using namespace Foreman::Action;

////////////////////////////////////////////////
// foreman_action_script_manager_new
////////////////////////////////////////////////

ForemanActionScriptManager* foreman_action_script_manager_new()
{
  return new DefaultScriptManager();
}

////////////////////////////////////////////////
// foreman_action_script_manager_delete
////////////////////////////////////////////////

bool foreman_action_script_manager_delete(ForemanActionScriptManager* mgr)
{
  if (!mgr)
    return false;
  delete (ScriptManager*)mgr;
  return true;
}

////////////////////////////////////////////////
// foreman_action_script_manager_addmethod
////////////////////////////////////////////////

bool foreman_action_script_manager_addmethod(ForemanActionScriptManager* mgr, ForemanActionMethod *method, ForemanError* err)
{
  if (!mgr || !method || !err)
    return false;
  return ((ScriptManager*)mgr)->addMethod((Method *)method, (Foreman::Error*)err);
}

////////////////////////////////////////////////
// foreman_action_script_manager_excemethod
////////////////////////////////////////////////

bool foreman_action_script_manager_excemethod(ForemanActionScriptManager* mgr, const char* name, ForemanActionParameters* params, ForemanActionParameters* results, ForemanError* err)
{
  if (!mgr || !name || !params || !results || !err)
    return false;
  return ((ScriptManager*)mgr)->execMethod(name, (Parameters*)params, (Parameters*)results, (Foreman::Error*)err);
}
