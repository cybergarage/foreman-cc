/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_LUA_H_
#define _FOREMANCC_ACTION_LUA_H_

#include <foreman/Platform.h>

#if defined(FOREMAN_SUPPORT_LUA)

#include <foreman/action/Script.h>
#include <string>

extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // LuaEngine
  ////////////////////////////////////////////////

  class LuaEngine : public ScriptEngine {

public:
    static const std::string LANGUAGE;

public:
    LuaEngine();
    ~LuaEngine();

    bool compile(Script* script, Error* error);
    bool run(Script* script, const Parameters* params, Parameters* results, Error* error);

    bool popString(std::string* result) const;
    bool popError(Error* error) const;

private:
    lua_State* luaState;
  };
}
}

#endif

#endif
