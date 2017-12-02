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

#include <foreman/action/impl/Lua.h>
#include <foreman/common/Errors.h>

#if defined(FOREMAN_SUPPORT_LUA)

const std::string Foreman::Action::LuaEngine::LANGUAGE = "lua";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Foreman::Action::LuaEngine::LuaEngine()
    : ScriptEngine(LANGUAGE)
{
  this->luaState = luaL_newstate();

  luaL_openlibs(this->luaState);
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

bool Foreman::Action::LuaEngine::compile(const Script* luaScript, Error* err) const
{
  const byte* scriptCode = luaScript->getCode();
  int loadingResult = luaL_loadstring(this->luaState, (const char*)scriptCode);
  lua_settop(this->luaState, 0);
  return (loadingResult == 0) ? true : false;
  ;
}

////////////////////////////////////////////////
// run
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

bool Foreman::Action::LuaEngine::run(const Script* script, const Parameters* params, Parameters* results, Error* error) const
{
  lock();

  int nStack = lua_gettop(this->luaState);

  if (luaL_loadstring(this->luaState, (const char*)script->getCode()) != 0) {
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

  lua_getglobal(this->luaState, script->getName());
  // FIXME
  //lua_pushstring(this->luaState, params.c_str());

  nStack = lua_gettop(this->luaState);

  int callResult = lua_pcall(this->luaState, 1, 1, 0);
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
