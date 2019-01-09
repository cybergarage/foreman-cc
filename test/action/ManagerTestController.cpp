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

#include <foreman/Client.h>
#include <foreman/Const.h>
#include <foreman/register/impl/StoreImpl.h>

#include "../ForemanTest.h"
#include "ManagerTestController.h"

using namespace Foreman::Action;

#define FOREMANCC_TEST_SCRIPT_REPETITION_COUNT 5

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

  for (int n = 0; n < FOREMANCC_TEST_SCRIPT_REPETITION_COUNT; n++) {
    //testEcho(mgr);
    //testRegister(mgr);
#if defined(FOREMAN_SUPPORT_PYTHON)
    testQuery(mgr);
#endif
  }

  BOOST_CHECK(regStore.close());
}

////////////////////////////////////////////////
// testEcho
////////////////////////////////////////////////

void ManagerTestController::testEcho(Manager* mgr, bool checkResultParameters)
{
  Parameters params;
  auto param = new String();
  param->setName(FOREMANCC_TEST_SCRIPT_ECHO_PARAM_NAME);
  param->setValue(FOREMANCC_TEST_SCRIPT_ECHO_PARAM_VALUE);
  params.addParameter(param);

  Parameters results;
  Error err;
  auto isExecuted = mgr->execMethod(FOREMANCC_TEST_SCRIPT_ECHO_METHOD, &params, &results, &err);
  BOOST_CHECK(isExecuted);
  if (!isExecuted)
    return;

  if (!checkResultParameters)
    return;

  auto echoMsg = results.getParameter(FOREMANCC_TEST_SCRIPT_ECHO_PARAM_NAME);
  BOOST_CHECK(echoMsg);
  if (!echoMsg)
    return;

  BOOST_CHECK(echoMsg->isString());
  auto echoStr = dynamic_cast<const String*>(echoMsg);
  BOOST_CHECK(echoStr);
  BOOST_CHECK_EQUAL(FOREMANCC_TEST_SCRIPT_ECHO_PARAM_VALUE, echoStr->getValue());
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
  param->setName(FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD_PARAM_NAME);
  param->setValue(FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD_PARAM_VALUE);
  params.addParameter(param);

  results.clear();
  isSuccess = mgr->execMethod(FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD, &params, &results, &err);
  BOOST_CHECK(isSuccess);
  if (!isSuccess)
    return;

  // Get registry

  params.clear();
  param = new String();
  param->setName(FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD_PARAM_NAME);
  params.addParameter(param);

  results.clear();
  isSuccess = mgr->execMethod(FOREMANCC_TEST_SCRIPT_GET_REGISTER_METHOD, &params, &results, &err);
  BOOST_CHECK(isSuccess);
  if (!isSuccess)
    return;

  auto retParam = results.getParameter(FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD_PARAM_NAME);
  BOOST_CHECK(retParam);
  if (retParam) {
    BOOST_CHECK(retParam->isString());
    if (retParam->isString()) {
      auto retString = dynamic_cast<String*>(retParam);
      BOOST_CHECK(retString);
      BOOST_CHECK_EQUAL(retString->getValue().c_str(), FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD_PARAM_VALUE);
    }
  }

  // Remove registry

  params.clear();
  param = new String();
  param->setName(FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD_PARAM_NAME);
  params.addParameter(param);
  
   
  results.clear();
  isSuccess = mgr->execMethod(FOREMANCC_TEST_SCRIPT_REMOVE_REGISTER_METHOD, &params, &results, &err);
  BOOST_CHECK(isSuccess);
}

////////////////////////////////////////////////
// testQuery
////////////////////////////////////////////////

void ManagerTestController::testQuery(Manager* mgr)
{
  Foreman::Client client;

  // Check whether foremand is runnging
  if (!client.ping())
    return;

  std::vector<std::string> queries;
  queries.push_back("EXPORT FROM CONFIG");
  queries.push_back("SET (query_test_reg, 1.0) INTO REGISTER");
  queries.push_back("EXPORT FROM REGISTER WHERE name == query_test_reg");

  for (auto query : queries) {
    Parameters params;
    auto param = new String();
    param->setName(FOREMANCC_TEST_SCRIPT_EXECUTE_QUERY_METHOD_PARAM_NAME);
    param->setValue(query.c_str());
    params.addParameter(param);

    Parameters results;
    Error err;

    // Execute Query

    BOOST_CHECK(mgr->execMethod(FOREMANCC_TEST_SCRIPT_EXECUTE_QUERY_METHOD, &params, &results, &err));

    // Post Query

    BOOST_CHECK(mgr->execMethod(FOREMANCC_TEST_SCRIPT_POST_QUERY_METHOD, &params, &results, &err));
  }
}
