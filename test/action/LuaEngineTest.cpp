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

  LuaEngine* engine = new LuaEngine();

  // hello

  static const char* LUA_ECHO_CODE = "function " FOREMANCC_SCRIPT_ECHO_METHOD "(params)\n"
                                     "  return true, params\n"
                                     "end";

  auto hello = new Foreman::Action::LuaMethod();
  BOOST_CHECK(hello->setName(FOREMANCC_SCRIPT_ECHO_METHOD));
  BOOST_CHECK(hello->setCode(LUA_ECHO_CODE));
  BOOST_CHECK(mgr.addMethod(hello, &err));

  delete engine;
}

BOOST_AUTO_TEST_SUITE_END()

#endif
