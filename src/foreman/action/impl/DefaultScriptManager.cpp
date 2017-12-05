/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>

#include <foreman/action/impl/ScriptImpl.h>

////////////////////////////////////////////////
// DefaultScriptManager
////////////////////////////////////////////////

Foreman::Action::DefaultScriptManager::DefaultScriptManager()
{
#if defined(FOREMAN_SUPPORT_PYTHON)
  addEngine(new PythonEngine());
#endif

#if defined(FOREMAN_SUPPORT_LUA)
  addEngine(new LuaEngine());
#endif
}
