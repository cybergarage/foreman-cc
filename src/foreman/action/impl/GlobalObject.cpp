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

/****************************************
 * SetGlobalRegisterStore
 ****************************************/

void Foreman::Action::SetGlobalRegisterStore(Foreman::Register::Store* store)
{
  gForemanGlobalRegisterStore = store;
}

/****************************************
 * round_python_getlocalnode
 ****************************************/

Foreman::Register::Store* Foreman::Action::GetGlobalRegisterStore()
{
  return gForemanGlobalRegisterStore;
}
