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
#include <foreman/action/impl/GlobalObject.h>

using namespace Foreman::Action;

////////////////////////////////////////////////
// foreman_action_manager_new
////////////////////////////////////////////////

ForemanActionManager* foreman_action_manager_new()
{
  return new Manager();
}

////////////////////////////////////////////////
// foreman_action_manager_delete
////////////////////////////////////////////////

bool foreman_action_manager_delete(ForemanActionManager* mgr)
{
  if (!mgr)
    return false;
  delete (Manager*)mgr;
  return true;
}

////////////////////////////////////////////////
// foreman_action_manager_setregisterstore
////////////////////////////////////////////////

bool foreman_action_manager_setregisterstore(ForemanActionManager* mgr, ForemanRegisterStore* store)
{
  if (!mgr || !store)
    return false;
  return ((Manager*)mgr)->setRegisterStore((Foreman::Register::Store*)store);
}

////////////////////////////////////////////////
// foreman_action_manager_setregisterstore
////////////////////////////////////////////////

bool foreman_action_manager_setregistrystore(ForemanActionManager* mgr, ForemanRegistryStore* store)
{
  if (!mgr || !store)
    return false;
  return ((Manager*)mgr)->setRegistryStore((Foreman::Registry::Store*)store);
}

////////////////////////////////////////////////
// foreman_action_manager_setregisterstore
////////////////////////////////////////////////

bool foreman_action_manager_setmetricstore(ForemanActionManager* mgr, ForemanMetricStore* store)
{
  if (!mgr || !store)
    return false;
  return ((Manager*)mgr)->setMetricStore((Foreman::Metric::Store*)store);
}

////////////////////////////////////////////////
// foreman_action_manager_hasengine
////////////////////////////////////////////////

bool foreman_action_manager_hasengine(ForemanActionManager* mgr, const char* name)
{
  if (!mgr || !name)
    return false;
  return ((Manager*)mgr)->hasEngine(name);
}

////////////////////////////////////////////////
// foreman_action_manager_addmethod
////////////////////////////////////////////////

bool foreman_action_manager_addmethod(ForemanActionManager* mgr, ForemanActionMethod* method, ForemanError* err)
{
  if (!mgr || !method || !err)
    return false;
  return ((Manager*)mgr)->addMethod((Method*)method, (Foreman::Error*)err);
}

////////////////////////////////////////////////
// foreman_action_manager_hasmethod
////////////////////////////////////////////////

bool foreman_action_manager_hasmethod(ForemanActionManager* mgr, const char* name)
{
  if (!mgr || !name)
    return false;
  return ((Manager*)mgr)->hasMethod(name);
}

////////////////////////////////////////////////
// foreman_action_manager_execmethod
////////////////////////////////////////////////

bool foreman_action_manager_execmethod(ForemanActionManager* mgr, const char* name, ForemanActionParameters* params, ForemanActionParameters* results, ForemanError* err)
{
  if (!mgr || !name || !params || !results || !err)
    return false;
  return ((Manager*)mgr)->execMethod(name, (Parameters*)params, (Parameters*)results, (Foreman::Error*)err);
}
