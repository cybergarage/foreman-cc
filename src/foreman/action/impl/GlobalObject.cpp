/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/impl/GlobalObject.h>

static Foreman::Register::Store* gForemanGlobalRegisterStore = NULL;
static Foreman::Registry::Store* gForemanGlobalRegistryStore = NULL;
static Foreman::Metric::Store* gForemanGlobalMetricStore = NULL;

/****************************************
 * SetGlobalRegisterStore
 ****************************************/

void Foreman::Action::SetGlobalRegisterStore(Foreman::Register::Store* store)
{
  gForemanGlobalRegisterStore = store;
}

/****************************************
 * GetGlobalRegisterStore
 ****************************************/

Foreman::Register::Store* Foreman::Action::GetGlobalRegisterStore()
{
  return gForemanGlobalRegisterStore;
}

/****************************************
 * SetGlobalRegistryStore
 ****************************************/

void Foreman::Action::SetGlobalRegistryStore(Foreman::Registry::Store* store)
{
  gForemanGlobalRegistryStore = store;
}

/****************************************
 * GetGlobalRegistryStore
 ****************************************/

Foreman::Registry::Store* Foreman::Action::GetGlobalRegistryStore()
{
  return gForemanGlobalRegistryStore;
}

/****************************************
 * SetGlobalMetricStore
 ****************************************/

void Foreman::Action::SetGlobalMetricStore(Foreman::Metric::Store* store)
{
  gForemanGlobalMetricStore = store;
}

/****************************************
 * GetGlobalMetricStore
 ****************************************/

Foreman::Metric::Store* Foreman::Action::GetGlobalMetricStore()
{
  return gForemanGlobalMetricStore;
}
