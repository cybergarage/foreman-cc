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

#include <foreman/Const.h>
#include <foreman/action/impl/GlobalObject.h>
#include <foreman/action/impl/Lua.h>
#include <foreman/common/Errors.h>

/****************************************
 * foreman_lua_setregister
 ****************************************/

int foreman_lua_setregister(lua_State* L)
{
  bool isSuccess = false;

  std::string key = luaL_checkstring(L, 1);
  std::string val = luaL_checkstring(L, 2);

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (store) {
    Foreman::Register::Object obj;
    obj.setKey(key);
    obj.setData(val);

    Foreman::Error err;
    isSuccess = store->setObject(&obj, &err);
  }

  lua_pushboolean(L, isSuccess);

  return 1;
}

/****************************************
 * foreman_lua_getregister
 ****************************************/

int foreman_lua_getregister(lua_State* L)
{
  bool isSuccess = false;
  std::string regData;

  std::string key = luaL_checkstring(L, 1);

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (store && (0 < key.length())) {

    Foreman::Register::Object obj;
    Foreman::Error err;
    isSuccess = store->getObject(key, &obj, &err);

    if (isSuccess) {
      regData = obj.getData();
    }
  }

  lua_pushboolean(L, isSuccess);
  lua_pushstring(L, regData.c_str());

  return 2;
}

/****************************************
 * foreman_lua_removeregister
 ****************************************/

int foreman_lua_removeregister(lua_State* L)
{
  bool isSuccess = false;

  std::string key = luaL_checkstring(L, 1);

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (store) {
    Foreman::Error err;
    isSuccess = store->removeObject(key, &err);
  }

  lua_pushboolean(L, isSuccess);

  return 1;
}

////////////////////////////////////////////////
// regsterFunctions
////////////////////////////////////////////////

void Foreman::Action::LuaEngine::regsterFunctions()
{
  lua_register(this->luaState, FOREMANCC_SYSTEM_FUNCTION_SETREGISTER, foreman_lua_setregister);
  lua_register(this->luaState, FOREMANCC_SYSTEM_FUNCTION_GETREGISTER, foreman_lua_getregister);
  lua_register(this->luaState, FOREMANCC_SYSTEM_FUNCTION_REMOVEREGISTER, foreman_lua_removeregister);
}

#endif
