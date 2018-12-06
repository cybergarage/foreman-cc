/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/Manager.h>
#include <foreman/action/impl/EngineImpl.h>
#include <foreman/common/Errors.h>

////////////////////////////////////////////////
// DefaultManager
////////////////////////////////////////////////

Foreman::Action::DefaultManager::DefaultManager()
{
  addEngine(new SystemEngine());

#if defined(FOREMAN_SUPPORT_PYTHON)
  addEngine(new PythonEngine());
#endif

#if defined(FOREMAN_SUPPORT_LUA)
  addEngine(new LuaEngine());
#endif
}

Foreman::Action::DefaultManager::~DefaultManager()
{
}
