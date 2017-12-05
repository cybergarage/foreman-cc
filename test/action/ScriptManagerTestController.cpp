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
#include <foreman/Const.h>

#include "../ForemanTest.h"
#include "ScriptManagerTestController.h"

using namespace Foreman::Action;

////////////////////////////////////////////////
// ScriptManagerTestController
////////////////////////////////////////////////

ScriptManagerTestController::ScriptManagerTestController() {}

ScriptManagerTestController::~ScriptManagerTestController() {}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

void ScriptManagerTestController::run(ScriptManager* scriptMgr)
{
  testHello(scriptMgr);
}

////////////////////////////////////////////////
// testHello
////////////////////////////////////////////////

void ScriptManagerTestController::testHello(ScriptManager* scriptMgr)
{
  Parameters params;
  auto msg = new String();
  msg->setName(FOREMANCC_SCRIPT_HELLO_ECHO_PARAM_NAME);
  msg->setValue(FOREMANCC_SCRIPT_HELLO_ECHO_PARAM_VALUE);
  params.addParameter(msg);

  Parameters results;
  Error err;
  auto isExecuted = scriptMgr->execMethod(FOREMANCC_SCRIPT_HELLO_ECHO_METHOD, &params, &results, &err);
  BOOST_CHECK(isExecuted);
  if (!isExecuted)
    return;

  auto echoMsg = results.getParameter(FOREMANCC_SCRIPT_HELLO_ECHO_PARAM_NAME);
  BOOST_CHECK(echoMsg);
  if (!echoMsg)
    return;

  BOOST_CHECK(echoMsg->isString());
  auto echoStr = dynamic_cast<const String*>(echoMsg);
  BOOST_CHECK(echoStr);
  BOOST_CHECK_EQUAL(FOREMANCC_SCRIPT_HELLO_ECHO_PARAM_VALUE, echoStr->getValue());
}
