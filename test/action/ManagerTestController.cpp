/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <array>
#include <boost/test/unit_test.hpp>
#include <string>

#include <foreman/Client.h>
#include <foreman/Const.h>
#include <foreman/log/Log.h>
#include <foreman/register/impl/StoreImpl.h>

#include "../ForemanTest.h"
#include "ManagerTestController.h"

using namespace Foreman::Action;

#define FOREMANCC_TEST_SCRIPT_REPETITION_COUNT 10

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

  auto logger = Foreman::Log::Logger::GetSharedInstance();
  BOOST_CHECK(logger);
  logger->setLevel(Foreman::Log::LogLevel::ALL);
  Foreman::Log::Outputter* nullOutputter = new Foreman::Log::NullOutputter();
  BOOST_CHECK(nullOutputter);
  logger->addOutputter(nullOutputter);

  for (int n = 0; n < FOREMANCC_TEST_SCRIPT_REPETITION_COUNT; n++) {
    bool isSuccess = true;
    isSuccess &= testEcho(mgr);
    isSuccess &= testRegister(mgr);
#if defined(FOREMAN_SUPPORT_PYTHON)
    isSuccess &= testQuery(mgr);
    isSuccess &= testLog(mgr);
#if defined(__APPLE__) // FIXME On CentOS
    isSuccess &= testLogX(mgr);
#endif
#endif
    if (!isSuccess)
      break;
  }
  logger->clear();
  BOOST_CHECK(regStore.close());
}

////////////////////////////////////////////////
// testEcho
////////////////////////////////////////////////

bool ManagerTestController::testEcho(Manager* mgr, bool checkResultParameters)
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
    return false;

  if (!checkResultParameters)
    return false;

  auto echoMsg = results.getParameter(FOREMANCC_TEST_SCRIPT_ECHO_PARAM_NAME);
  BOOST_CHECK(echoMsg);
  if (!echoMsg)
    return false;

  BOOST_CHECK(echoMsg->isString());
  auto echoStr = dynamic_cast<const String*>(echoMsg);
  BOOST_CHECK(echoStr);
  BOOST_CHECK_EQUAL(FOREMANCC_TEST_SCRIPT_ECHO_PARAM_VALUE, echoStr->getValue());

  return true;
}

////////////////////////////////////////////////
// testRegister
////////////////////////////////////////////////

bool ManagerTestController::testRegister(Manager* mgr)
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
    return false;

  // Get registry

  params.clear();
  param = new String();
  param->setName(FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD_PARAM_NAME);
  params.addParameter(param);

  results.clear();
  isSuccess = mgr->execMethod(FOREMANCC_TEST_SCRIPT_GET_REGISTER_METHOD, &params, &results, &err);
  BOOST_CHECK(isSuccess);
  if (!isSuccess)
    return false;

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
  if (!isSuccess)
    return false;

  return true;
}

////////////////////////////////////////////////
// testQuery
////////////////////////////////////////////////

bool ManagerTestController::testQuery(Manager* mgr)
{
  Foreman::Client client;

  // Check whether foremand is runnging
  if (!client.ping())
    return true;

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

    BOOST_CHECK_MESSAGE(mgr->execMethod(FOREMANCC_TEST_SCRIPT_EXECUTE_QUERY_METHOD, &params, &results, &err), err);

    // Post Query

    BOOST_CHECK_MESSAGE(mgr->execMethod(FOREMANCC_TEST_SCRIPT_POST_QUERY_METHOD, &params, &results, &err), err);
  }

  return true;
}

////////////////////////////////////////////////
// testLog
////////////////////////////////////////////////

bool ManagerTestController::testLog(Manager* mgr)
{
  Parameters params;
  Parameters results;
  Error err;

  params.clear();
  results.clear();
  BOOST_CHECK_MESSAGE(mgr->execMethod(FOREMANCC_TEST_SCRIPT_LOG_METHOD, &params, &results, &err), err);

  auto outputters = results.getParameter("outputters");
  if (outputters) {
    BOOST_CHECK(outputters->isInteger());
    auto n_outputters = dynamic_cast<Integer*>(outputters)->getValue();
    BOOST_CHECK(n_outputters == 1);
  }
  else {
    return false;
  }

  return true;
}

////////////////////////////////////////////////
// testLog_*
////////////////////////////////////////////////

bool ManagerTestController::testLogX(Manager* mgr)
{
  std::array<std::string, 6> levels {
    std::string(FOREMANCC_TEST_SCRIPT_LOG_FATAL_METHOD),
    std::string(FOREMANCC_TEST_SCRIPT_LOG_ERROR_METHOD),
    std::string(FOREMANCC_TEST_SCRIPT_LOG_WARN_METHOD),
    std::string(FOREMANCC_TEST_SCRIPT_LOG_INFO_METHOD),
    std::string(FOREMANCC_TEST_SCRIPT_LOG_DEBUG_METHOD),
    std::string(FOREMANCC_TEST_SCRIPT_LOG_TRACE_METHOD)
  };
  for (auto itr = levels.cbegin(); itr != levels.cend(); itr++) {
    Parameters params;
    Parameters results;
    Error err;

    params.clear();
    results.clear();
    BOOST_CHECK_MESSAGE(mgr->execMethod(*itr, &params, &results, &err), err);
    auto outputters = results.getParameter("outputters");
    if (outputters) {
      BOOST_CHECK(outputters->isInteger());
      auto n_outputters = dynamic_cast<Integer*>(outputters)->getValue();
      BOOST_CHECK(n_outputters == 1);
    }
    else {
      return false;
    }
  }

  return true;
}
