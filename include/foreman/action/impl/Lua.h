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

#include <foreman/action/Engine.h>
#include <string>

extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // LuaMethod
  ////////////////////////////////////////////////

  class LuaMethod : public Method {
public:
    LuaMethod();
    ~LuaMethod();
  };

  ////////////////////////////////////////////////
  // LuaTable
  ////////////////////////////////////////////////

  class LuaTable : Parameters {
public:
    LuaTable();
    ~LuaTable();
  };

  ////////////////////////////////////////////////
  // LuaEngine
  ////////////////////////////////////////////////

  class LuaEngine : public ScriptEngine {

public:
    static const std::string LANGUAGE;

public:
    LuaEngine();
    ~LuaEngine();

    bool compile(Method* method, Error* error);
    bool run(Method* method, const Parameters* params, Parameters* results, Error* error);

private:
    void regsterFunctions();

    bool pushParameters(const Parameters* params);
    bool popString(std::string* result) const;
    bool popBoolean(bool* result) const;
    bool popParameters(Parameters* params);
    bool popError(Error* error) const;
    
    lua_State* luaState;
  };
}
}

#endif

#endif
