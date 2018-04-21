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
#include <foreman/register/impl/StoreImpl.h>

#include "../ForemanTest.h"
#include "ManagerTestController.h"

using namespace Foreman::Action;

////////////////////////////////////////////////
// ManagerTestController.h
////////////////////////////////////////////////

ManagerTestController::ManagerTestController() {}

ManagerTestController::~ManagerTestController() {}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

void ManagerTestController::run(Manager* mgr)
{
  Foreman::Register::MemStore regStore;
  BOOST_CHECK(regStore.open());
  BOOST_CHECK(mgr->setRegisterStore(&regStore));

  testEcho(mgr);
  testRegister(mgr);

  BOOST_CHECK(regStore.close());
}

////////////////////////////////////////////////
// testEcho
////////////////////////////////////////////////

void ManagerTestController::testEcho(Manager* mgr, bool checkResultParameters)
{
  Parameters params;
  auto param = new String();
  param->setName(FOREMANCC_SCRIPT_ECHO_PARAM_NAME);
  param->setValue(FOREMANCC_SCRIPT_ECHO_PARAM_VALUE);
  params.addParameter(param);

  Parameters results;
  Error err;
  auto isExecuted = mgr->execMethod(FOREMANCC_SCRIPT_ECHO_METHOD, &params, &results, &err);
  BOOST_CHECK(isExecuted);
  if (!isExecuted)
    return;

  if (!checkResultParameters)
    return;
  
  auto echoMsg = results.getParameter(FOREMANCC_SCRIPT_ECHO_PARAM_NAME);
  BOOST_CHECK(echoMsg);
  if (!echoMsg)
    return;

  BOOST_CHECK(echoMsg->isString());
  auto echoStr = dynamic_cast<const String*>(echoMsg);
  BOOST_CHECK(echoStr);
  BOOST_CHECK_EQUAL(FOREMANCC_SCRIPT_ECHO_PARAM_VALUE, echoStr->getValue());
}

////////////////////////////////////////////////
// testRegister
////////////////////////////////////////////////

void ManagerTestController::testRegister(Manager* mgr)
{
  Parameters params;
  Parameters results;
  String* param;
  Error err;
  bool isSuccess;

  // Set registry

  params.clear();
  param = new String();
  param->setName(FOREMANCC_SCRIPT_SET_REGISTER_METHOD_PARAM_NAME);
  param->setValue(FOREMANCC_SCRIPT_SET_REGISTER_METHOD_PARAM_VALUE);
  params.addParameter(param);

  results.clear();
  isSuccess = mgr->execMethod(FOREMANCC_SCRIPT_SET_REGISTER_METHOD, &params, &results, &err);
  BOOST_CHECK(isSuccess);
  if (!isSuccess)
    return;

  // Get registry

  params.clear();
  param = new String();
  param->setName(FOREMANCC_SCRIPT_SET_REGISTER_METHOD_PARAM_NAME);
  params.addParameter(param);

  results.clear();
  isSuccess = mgr->execMethod(FOREMANCC_SCRIPT_GET_REGISTER_METHOD, &params, &results, &err);
  BOOST_CHECK(isSuccess);
  if (!isSuccess)
    return;

  auto retParam = results.getParameter(FOREMANCC_SCRIPT_SET_REGISTER_METHOD_PARAM_NAME);
  BOOST_CHECK(retParam);
  if (retParam) {
    BOOST_CHECK(retParam->isString());
    auto retString = dynamic_cast<String*>(retParam);
    BOOST_CHECK(retString);
    BOOST_CHECK_EQUAL(retString->getValue().c_str(), FOREMANCC_SCRIPT_SET_REGISTER_METHOD_PARAM_VALUE);
  }

  // Remove registry

  // FIXME : Python error
  /*
  params.clear();
  param = new String();
  param->setName(FOREMANCC_SCRIPT_SET_REGISTER_METHOD_PARAM_NAME);
  params.addParameter(param);
  
   
  results.clear();
  isSuccess = mgr->execMethod(FOREMANCC_SCRIPT_REMOVE_REGISTER_METHOD, &params, &results, &err);
  BOOST_CHECK(isSuccess);
   */
}
