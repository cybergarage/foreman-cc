/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Platform.h>

#if defined(FOREMAN_SUPPORT_LUA)

#include <foreman/action/impl/Lua.h>

////////////////////////////////////////////////
// LuaMethod
////////////////////////////////////////////////

Foreman::Action::LuaMethod::LuaMethod()
    : Foreman::Action::Method(Foreman::Action::LuaEngine::LANGUAGE)
{
}

Foreman::Action::LuaMethod::~LuaMethod()
{
}

#endif
