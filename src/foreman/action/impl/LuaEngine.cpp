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

#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>

#include <foreman/Const.h>
#include <foreman/action/impl/Lua.h>
#include <foreman/common/Errors.h>

const std::string Foreman::Action::LuaEngine::LANGUAGE = FOREMANCC_ACTION_SCRIPT_ENGINE_LUA;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Foreman::Action::LuaEngine::LuaEngine()
    : ScriptEngine(LANGUAGE)
{
  this->luaState = luaL_newstate();
  luaL_openlibs(this->luaState);
  regsterFunctions();
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

Foreman::Action::LuaEngine::~LuaEngine()
{
  lua_close(this->luaState);
}

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

bool Foreman::Action::LuaEngine::compile(Method* luaScript, Error* error)
{
  const byte* scriptCode = luaScript->getCode();
  int loadingResult = luaL_loadstring(this->luaState, (const char*)scriptCode);
  lua_settop(this->luaState, 0);
  return (loadingResult == 0) ? true : false;
}

////////////////////////////////////////////////
// pushParameters
////////////////////////////////////////////////

bool Foreman::Action::LuaEngine::pushParameters(const Parameters* params)
{
  lua_newtable(this->luaState);
  for (auto param : *params) {
    lua_pushstring(this->luaState, param->getName());
    switch (param->getType()) {
      case IntegerType: {
        auto iparam = dynamic_cast<const Integer*>(param.get());
        lua_pushinteger(this->luaState, iparam->getValue());
      } break;
      case RealType: {
        auto rparam = dynamic_cast<const Real*>(param.get());
        lua_pushnumber(this->luaState, rparam->getValue());
      } break;
      case BoolType: {
        auto bparam = dynamic_cast<const Bool*>(param.get());
        lua_pushboolean(this->luaState, bparam->getValue());
      } break;
      case StringType: {
        auto sparam = dynamic_cast<const String*>(param.get());
        lua_pushstring(this->luaState, sparam->getValue().c_str());
      } break;
      default:
        return false;
    }
    lua_settable(this->luaState, -3);
  }
  
  return true;
}

////////////////////////////////////////////////
// popString
////////////////////////////////////////////////

bool Foreman::Action::LuaEngine::popString(std::string* result) const
{
  int nStack = lua_gettop(this->luaState);
  if (nStack <= 0)
    return false;

  if (lua_isstring(this->luaState, -1)) {
    *result = lua_tostring(this->luaState, -1);
    lua_pop(this->luaState, 1);
    return true;
  }

  if (lua_isboolean(this->luaState, -1)) {
    *result = lua_toboolean(this->luaState, -1) ? "true" : "false";
    lua_pop(this->luaState, 1);
    return true;
  }

  if (lua_isnumber(this->luaState, -1)) {
    double dresult = lua_tonumber(this->luaState, -1);
    *result = boost::lexical_cast<std::string>(dresult);
    lua_pop(this->luaState, 1);
    return true;
  }

  return false;
}

////////////////////////////////////////////////
// popBoolean
////////////////////////////////////////////////

bool Foreman::Action::LuaEngine::popBoolean(bool* result) const
{
  int nStack = lua_gettop(this->luaState);
  if (nStack <= 0)
    return false;

  if (!lua_isboolean(this->luaState, -1))
    return false;

  *result = (lua_toboolean(this->luaState, -1) ? true : false);
  lua_pop(this->luaState, 1);

  return true;
}

////////////////////////////////////////////////
// popParameters
////////////////////////////////////////////////

bool Foreman::Action::LuaEngine::popParameters(Parameters* params)
{
  int nStack = lua_gettop(this->luaState);
  if (nStack <= 0)
    return false;

  if (!lua_istable(this->luaState, -1))
    return false;

  lua_pushnil(this->luaState);
  while (lua_next(this->luaState, -2) != 0) {
    lua_pushvalue(this->luaState, -2);

    auto name = lua_tostring(this->luaState, -1);

    Parameter *param = NULL;
    if (lua_isstring(this->luaState, -2)) {
      param = new String();
      ((String *)param)->setValue(lua_tostring(this->luaState, -2));
    }
    else if (lua_isboolean(this->luaState, -2)) {
      param = new Bool();
      ((Bool *)param)->setValue(lua_toboolean(this->luaState, -2));
    }
    else if (lua_isnumber(this->luaState, -2)) {
      param = new Real();
      ((Real *)param)->setValue(lua_tonumber(this->luaState, -2));
    }
    else if (lua_isinteger(this->luaState, -2)) {
      param = new Integer();
      ((Integer *)param)->setValue(lua_tointeger(this->luaState, -2));
    }

    if (param) {
      param->setName(name);
      params->addParameter(param);
    }

    lua_pop(this->luaState, 2);
  }

  lua_pop(this->luaState, 1);

  return true;
}

////////////////////////////////////////////////
// popError
////////////////////////////////////////////////

bool Foreman::Action::LuaEngine::popError(Error* error) const
{
  int nStack = lua_gettop(this->luaState);
  if (nStack <= 0)
    return false;

  FOREMANCC_ERROR_SET_ERRORNO(error, ERROR_INTERNAL_ERROR);
  error->setMessage(lua_tostring(this->luaState, -1));
  lua_pop(this->luaState, 1);

  return true;
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

bool Foreman::Action::LuaEngine::run(Method* method, const Parameters* params, Parameters* results, Error* error)
{
  lock();

  int nStack = lua_gettop(this->luaState);

  if (luaL_loadstring(this->luaState, (const char*)method->getCode()) != 0) {
    popError(error);
    unlock();
    return false;
  }

  nStack = lua_gettop(this->luaState);

  if (lua_pcall(this->luaState, 0, 0, 0) != 0) {
    popError(error);
    unlock();
    return false;
  }

  nStack = lua_gettop(this->luaState);

  lua_getglobal(this->luaState, method->getName().c_str());

  if (!pushParameters(params)) {
    popError(error);
    unlock();
    return false;
  }
  
  nStack = lua_gettop(this->luaState);

  bool isSuccess = false;
  int callResult = lua_pcall(this->luaState, 1, 2, 0);
  nStack = lua_gettop(this->luaState);
  if (callResult == 0) {
    if (popParameters(results)) {
      if (!popBoolean(&isSuccess)) {
        isSuccess = false;
      }
    }
    else {
      popError(error);
    }
  }
  else {
    popError(error);
  }

  nStack = lua_gettop(this->luaState);

  unlock();

  return isSuccess;
}

#endif
