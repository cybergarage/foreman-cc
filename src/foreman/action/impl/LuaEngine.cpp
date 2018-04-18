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
// run
////////////////////////////////////////////////

bool Foreman::Action::LuaEngine::popString(std::string* result) const
{
  int nStack = lua_gettop(this->luaState);
  if (nStack <= 0)
    return false;

  /*
  if (lua_istable(this->luaState, -1)) {
    *result = lua_tostring(this->luaState, -1);
    lua_pop(this->luaState, 1);
    return true;
  }
   */
  
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
// popTable
////////////////////////////////////////////////

bool Foreman::Action::LuaEngine::popTable(LuaTable* table) const
{
  int nStack = lua_gettop(this->luaState);
  if (nStack <= 0)
    return false;

  if (!lua_istable(this->luaState, -1))
    return false;

  //*result = lua_toboolean(this->luaState, -1) ? true : false;

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

  /*
  lua_newtable(this->luaState);
  for (auto param : *params) {
    lua_pushstring(this->luaState, param->getName());
    switch (param->getType()) {
      case IntegerType: {
        auto iparam = dynamic_cast<const Integer*>((*param));
        lua_pushinteger(this->luaState, iparam->getValue());
      } break;
      case RealType: {
        auto rparam = dynamic_cast<const Real*>(*param);
      } break;
      case BoolType: {
        auto bparam = dynamic_cast<const Bool*>(*param);
      } break;
      case StringType: {
        auto sparam = dynamic_cast<const String*>(*param);
      } break;
      default:
        return false;
    }
    lua_settable(this->luaState, -3);
  }
  */
  
  nStack = lua_gettop(this->luaState);

  int callResult = lua_pcall(this->luaState, 2, 2, 0);
  nStack = lua_gettop(this->luaState);
  if (callResult == 0) {
    // FIXME
    // popString(results);
  }
  else {
    popError(error);
  }

  nStack = lua_gettop(this->luaState);

  unlock();

  return (callResult == 0) ? true : false;
}

#endif
