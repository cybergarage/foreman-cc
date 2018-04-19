/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include "ManagerTestController.h"
#include <foreman/action/impl/Lua.h>

#if defined(FOREMAN_SUPPORT_LUA)

using namespace Foreman::Action;

BOOST_AUTO_TEST_SUITE(action)

BOOST_AUTO_TEST_CASE(LuaEngine)
{
  Foreman::Error err;
  Foreman::Action::Manager mgr;
  Foreman::Action::ManagerTestController testControllerr;

  // hello

  static const char* LUA_ECHO_CODE = "function " FOREMANCC_SCRIPT_ECHO_METHOD "(params)\n"
                                     "  return true, params\n"
                                     "end";

  auto hello = new Foreman::Action::LuaMethod();
  BOOST_CHECK(hello->setName(FOREMANCC_SCRIPT_ECHO_METHOD));
  BOOST_CHECK(hello->setCode(LUA_ECHO_CODE));
  BOOST_CHECK(mgr.addMethod(hello, &err));

  // set_registry

  static const char* LUA_SET_REGISTRY_CODE = "function " FOREMANCC_SCRIPT_SET_REGISTER_METHOD "(params)\n"
                                             "  for k, v in ipairs(params) do\n"
                                             "    " FOREMANCC_SYSTEM_FUNCTION_SETREGISTER "(k, v)\n"
                                             "  end\n"
                                             "  return true, {}\n"
                                             "end";

  auto setreg = new Foreman::Action::LuaMethod();
  BOOST_CHECK(setreg->setName(FOREMANCC_SCRIPT_SET_REGISTER_METHOD));
  BOOST_CHECK(setreg->setCode(LUA_SET_REGISTRY_CODE));
  BOOST_CHECK(mgr.addMethod(setreg, &err));

  // get_registry

  static const char* LUA_GET_REGISTRY_CODE = "function " FOREMANCC_SCRIPT_GET_REGISTER_METHOD "(params)\n"
                                             "  results = {}\n"
                                             "  for k, v in ipairs(params) do\n"
                                             "    ok, r = " FOREMANCC_SYSTEM_FUNCTION_GETREGISTER "(k)\n"
                                             "    if ok then\n"
                                             "      results[k] = r\n"
                                             "    end\n"
                                             "  end\n"
                                             "  return true, results\n"
                                             "end";

  auto getreg = new Foreman::Action::LuaMethod();
  BOOST_CHECK(getreg->setName(FOREMANCC_SCRIPT_GET_REGISTER_METHOD));
  BOOST_CHECK(getreg->setCode(LUA_GET_REGISTRY_CODE));
  BOOST_CHECK(mgr.addMethod(getreg, &err));

  // remove_registry

  static const char* LUA_REMOVE_REGISTRY_CODE = "function " FOREMANCC_SCRIPT_REMOVE_REGISTER_METHOD "(params)\n"
                                                "  for k, v in ipairs(params) do\n"
                                                "    " FOREMANCC_SYSTEM_FUNCTION_REMOVEREGISTER "(k)\n"
                                                "  end\n"
                                                "  return true, {}\n"
                                                "end";

  auto rmreg = new Foreman::Action::LuaMethod();
  BOOST_CHECK(rmreg->setName(FOREMANCC_SCRIPT_REMOVE_REGISTER_METHOD));
  BOOST_CHECK(rmreg->setCode(LUA_REMOVE_REGISTRY_CODE));
  BOOST_CHECK(mgr.addMethod(rmreg, &err));

  testControllerr.run(&mgr);
}

BOOST_AUTO_TEST_SUITE_END()

#endif
