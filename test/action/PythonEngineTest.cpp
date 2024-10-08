/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/format.hpp>
#include <boost/test/unit_test.hpp>

#include "ManagerTestController.h"
#include <foreman/action/impl/Python.h>

#if defined(FOREMAN_SUPPORT_PYTHON)

BOOST_AUTO_TEST_SUITE(action)
BOOST_AUTO_TEST_SUITE(python)

BOOST_AUTO_TEST_CASE(PythonParameters)
{
  Foreman::Action::PythonEngine pyEngine;
  Foreman::Action::Parameters params;

  // Integer
  auto iParam = new Foreman::Action::Integer();
  iParam->setName("iparam");
  iParam->setValue(1);
  params.addParameter(iParam);

  // Real
  auto rParam = new Foreman::Action::Real();
  rParam->setName("rparam");
  rParam->setValue(10.0);
  params.addParameter(rParam);

  // Bool
  auto bParam = new Foreman::Action::Bool();
  bParam->setName("bparam");
  bParam->setValue(true);
  params.addParameter(bParam);

  // String
  auto sParam = new Foreman::Action::String();
  sParam->setName("sparam");
  sParam->setValue("svalue");
  params.addParameter(sParam);

  // Set
  Foreman::Action::PythonParameters pyInParams;
  BOOST_CHECK(pyInParams.set(&params));
  BOOST_CHECK(pyInParams.equals(&params));

  // Get
  Foreman::Action::Parameters pyOutParams;
  BOOST_CHECK(pyInParams.get(&params));
  BOOST_CHECK(pyInParams.equals(&pyOutParams));
}

BOOST_AUTO_TEST_CASE(PythonEngine)
{
  Foreman::Error err;
  Foreman::Action::Manager mgr;
  Foreman::Action::ManagerTestController testController;

  mgr.addEngine(new Foreman::Action::PythonEngine());

  // error

  static const char* PY_ERROR_CODE = "def def def def\n";

  auto err_method = new Foreman::Action::PythonMethod();
  BOOST_CHECK(err_method->setName(FOREMANCC_TEST_SCRIPT_ERROR_METHOD));
  BOOST_CHECK(err_method->setCode(PY_ERROR_CODE));
  BOOST_CHECK(!mgr.addMethod(err_method, &err));
  BOOST_CHECK(err.hasMessage());
  BOOST_CHECK(err.hasDetailMessage());
  delete err_method; // Must delete an invalid method instance when it is not added

  // echo

  static const char* PY_ECHO_CODE = "def " FOREMANCC_TEST_SCRIPT_ECHO_METHOD "(params,results):\n"
                                    "  for key, value in params.items():\n"
                                    "    results[key] = value\n"
                                    "  return True\n";

  auto echo = new Foreman::Action::PythonMethod();
  BOOST_CHECK(echo->setName(FOREMANCC_TEST_SCRIPT_ECHO_METHOD));
  BOOST_CHECK(echo->setCode(PY_ECHO_CODE));
  BOOST_CHECK_MESSAGE(mgr.addMethod(echo, &err), err);

  // set_registry

  static const char* PY_SET_REGISTRY_CODE = "import " FOREMANCC_PRODUCT_NAME "\n"
                                            "def " FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD "(params,results):\n"
                                            "  for key, value in params.items():\n"
                                            "    " FOREMANCC_PRODUCT_NAME "." FOREMANCC_SYSTEM_FUNCTION_SETREGISTER "(key, value)\n"
                                            "  return True\n";

  auto setreg = new Foreman::Action::PythonMethod();
  BOOST_CHECK(setreg->setName(FOREMANCC_TEST_SCRIPT_SET_REGISTER_METHOD));
  BOOST_CHECK(setreg->setCode(PY_SET_REGISTRY_CODE));
  BOOST_CHECK_MESSAGE(mgr.addMethod(setreg, &err), err);

  // get_registry

  static const char* PY_GET_REGISTRY_CODE = "import " FOREMANCC_PRODUCT_NAME "\n"
                                            "def " FOREMANCC_TEST_SCRIPT_GET_REGISTER_METHOD "(params,results):\n"
                                            "  for reg_key, value in params.items():\n"
                                            "    reg_value = " FOREMANCC_PRODUCT_NAME "." FOREMANCC_SYSTEM_FUNCTION_GETREGISTER "(reg_key)\n"
                                            "    results[reg_key] = reg_value\n"
                                            "  return True\n";

  auto getreg = new Foreman::Action::PythonMethod();
  BOOST_CHECK(getreg->setName(FOREMANCC_TEST_SCRIPT_GET_REGISTER_METHOD));
  BOOST_CHECK(getreg->setCode(PY_GET_REGISTRY_CODE));
  BOOST_CHECK_MESSAGE(mgr.addMethod(getreg, &err), err);

  // remove_registry

  static const char* PY_REMOVE_REGISTRY_CODE = "import " FOREMANCC_PRODUCT_NAME "\n"
                                               "def " FOREMANCC_TEST_SCRIPT_REMOVE_REGISTER_METHOD "(params,results):\n"
                                               "  for key, value in params.items():\n"
                                               "    if " FOREMANCC_PRODUCT_NAME "." FOREMANCC_SYSTEM_FUNCTION_REMOVEREGISTER "(key) == False:\n"
                                               "      return False\n"
                                               "  return True\n";

  auto rmreg = new Foreman::Action::PythonMethod();
  BOOST_CHECK(rmreg->setName(FOREMANCC_TEST_SCRIPT_REMOVE_REGISTER_METHOD));
  BOOST_CHECK(rmreg->setCode(PY_REMOVE_REGISTRY_CODE));
  BOOST_CHECK_MESSAGE(mgr.addMethod(rmreg, &err), err);

  // execute_query

  static const char* PY_EXECUTE_QUERY_CODE = "import " FOREMANCC_PRODUCT_NAME "\n"
                                             "def " FOREMANCC_TEST_SCRIPT_EXECUTE_QUERY_METHOD "(params,results):\n"
                                             "  jsonRes = " FOREMANCC_PRODUCT_NAME "." FOREMANCC_SYSTEM_FUNCTION_EXECUTEQUERY "(params[\"" FOREMANCC_TEST_SCRIPT_EXECUTE_QUERY_METHOD_PARAM_NAME "\"])\n"
                                             "  if jsonRes is None:\n"
                                             "    return False\n"
                                             "  for key, value in jsonRes.items():\n"
                                             "    results[key] = value\n"
                                             "  return True\n";

  auto exQuery = new Foreman::Action::PythonMethod();
  BOOST_CHECK(exQuery->setName(FOREMANCC_TEST_SCRIPT_EXECUTE_QUERY_METHOD));
  BOOST_CHECK(exQuery->setCode(PY_EXECUTE_QUERY_CODE));
  BOOST_CHECK_MESSAGE(mgr.addMethod(exQuery, &err), err);

  // post_query

  static const char* PY_POST_QUERY_CODE = "import " FOREMANCC_PRODUCT_NAME "\n"
                                          "def " FOREMANCC_TEST_SCRIPT_POST_QUERY_METHOD "(params,results):\n"
                                          "  host = \"" FOREMANCC_TEST_SCRIPT_POST_QUERY_HOST "\"\n"
                                          "  port = " FOREMANCC_TEST_SCRIPT_POST_QUERY_PORT "\n"
                                          "  jsonRes = " FOREMANCC_PRODUCT_NAME "." FOREMANCC_SYSTEM_FUNCTION_POSTQUERY "(host, port, params[\"" FOREMANCC_TEST_SCRIPT_EXECUTE_QUERY_METHOD_PARAM_NAME "\"])\n"
                                          "  if jsonRes is None:\n"
                                          "    return False\n"
                                          "  for key, value in jsonRes.items():\n"
                                          "    results[key] = value\n"
                                          "  return True\n";

  auto postQuery = new Foreman::Action::PythonMethod();
  BOOST_CHECK(postQuery->setName(FOREMANCC_TEST_SCRIPT_POST_QUERY_METHOD));
  BOOST_CHECK(postQuery->setCode(PY_POST_QUERY_CODE));
  BOOST_CHECK_MESSAGE(mgr.addMethod(postQuery, &err), err);

  // log
  static const char* PY_LOG_CODE = "import " FOREMANCC_PRODUCT_NAME "\n"
                                   "def " FOREMANCC_TEST_SCRIPT_LOG_METHOD "(params, results):\n"
                                   "  log_message = \"" FOREMANCC_TEST_SCRIPT_LOG_MESSAGE "\"\n"
                                   "  log_level = \"" FOREMANCC_TEST_SCRIPT_LOG_LEVEL "\"\n"
                                   "  results[\"outputters\"] = " FOREMANCC_PRODUCT_NAME "." FOREMANCC_SYSTEM_FUNCTION_LOG "(log_message, log_level)\n"
                                   "  return True\n";

  auto foremanLogger = new Foreman::Action::PythonMethod();
  BOOST_CHECK(foremanLogger->setName(FOREMANCC_TEST_SCRIPT_LOG_METHOD));
  BOOST_CHECK(foremanLogger->setCode(PY_LOG_CODE));
  BOOST_CHECK_MESSAGE(mgr.addMethod(foremanLogger, &err), err);

#if defined(__APPLE__) // FIXME On CentOS

  // log_*
  static auto PY_LOG_CODE_TEMPLATE = "import " FOREMANCC_PRODUCT_NAME "\n"
                                     "def %s(params, results):\n"
                                     "  log_message = \"" FOREMANCC_TEST_SCRIPT_LOG_MESSAGE "\"\n"
                                     "  results[\"outputters\"] = " FOREMANCC_PRODUCT_NAME ".%s(log_message)\n"
                                     "  return True";

  auto foremanFatalLogger = new Foreman::Action::PythonMethod();
  auto testLogFatal = (boost::format(PY_LOG_CODE_TEMPLATE) % std::string(FOREMANCC_TEST_SCRIPT_LOG_FATAL_METHOD) % std::string(FOREMANCC_SYSTEM_FUNCTION_LOG_FATAL)).str().c_str();
  BOOST_CHECK(testLogFatal);
  BOOST_CHECK(foremanFatalLogger->setName(FOREMANCC_TEST_SCRIPT_LOG_FATAL_METHOD));
  BOOST_CHECK(foremanFatalLogger->setCode(testLogFatal));
  BOOST_CHECK_MESSAGE(mgr.addMethod(foremanFatalLogger, &err), err);

  auto foremanErrorLogger = new Foreman::Action::PythonMethod();
  auto testLogError = (boost::format(PY_LOG_CODE_TEMPLATE) % std::string(FOREMANCC_TEST_SCRIPT_LOG_ERROR_METHOD) % std::string(FOREMANCC_SYSTEM_FUNCTION_LOG_ERROR)).str().c_str();
  BOOST_CHECK(testLogError);
  BOOST_CHECK(foremanErrorLogger->setName(FOREMANCC_TEST_SCRIPT_LOG_ERROR_METHOD));
  BOOST_CHECK(foremanErrorLogger->setCode(testLogError));
  BOOST_CHECK_MESSAGE(mgr.addMethod(foremanErrorLogger, &err), err);

  auto foremanWarnLogger = new Foreman::Action::PythonMethod();
  auto testLogWarn = (boost::format(PY_LOG_CODE_TEMPLATE) % std::string(FOREMANCC_TEST_SCRIPT_LOG_WARN_METHOD) % std::string(FOREMANCC_SYSTEM_FUNCTION_LOG_WARN)).str().c_str();
  BOOST_CHECK(testLogWarn);
  BOOST_CHECK(foremanWarnLogger->setName(FOREMANCC_TEST_SCRIPT_LOG_WARN_METHOD));
  BOOST_CHECK(foremanWarnLogger->setCode(testLogWarn));
  BOOST_CHECK_MESSAGE(mgr.addMethod(foremanWarnLogger, &err), err);

  auto foremanInfoLogger = new Foreman::Action::PythonMethod();
  auto testLogInfo = (boost::format(PY_LOG_CODE_TEMPLATE) % std::string(FOREMANCC_TEST_SCRIPT_LOG_INFO_METHOD) % std::string(FOREMANCC_SYSTEM_FUNCTION_LOG_INFO)).str().c_str();
  BOOST_CHECK(testLogInfo);
  BOOST_CHECK(foremanInfoLogger->setName(FOREMANCC_TEST_SCRIPT_LOG_INFO_METHOD));
  BOOST_CHECK(foremanInfoLogger->setCode(testLogInfo));
  BOOST_CHECK_MESSAGE(mgr.addMethod(foremanInfoLogger, &err), err);

  auto foremanDebugLogger = new Foreman::Action::PythonMethod();
  auto testLogDebug = (boost::format(PY_LOG_CODE_TEMPLATE) % std::string(FOREMANCC_TEST_SCRIPT_LOG_DEBUG_METHOD) % std::string(FOREMANCC_SYSTEM_FUNCTION_LOG_DEBUG)).str().c_str();
  BOOST_CHECK(testLogDebug);
  BOOST_CHECK(foremanDebugLogger->setName(FOREMANCC_TEST_SCRIPT_LOG_DEBUG_METHOD));
  BOOST_CHECK(foremanDebugLogger->setCode(testLogDebug));
  BOOST_CHECK_MESSAGE(mgr.addMethod(foremanDebugLogger, &err), err);

  auto foremanTraceLogger = new Foreman::Action::PythonMethod();
  auto testLogTrace = (boost::format(PY_LOG_CODE_TEMPLATE) % std::string(FOREMANCC_TEST_SCRIPT_LOG_TRACE_METHOD) % std::string(FOREMANCC_SYSTEM_FUNCTION_LOG_TRACE)).str().c_str();
  BOOST_CHECK(testLogTrace);
  BOOST_CHECK(foremanTraceLogger->setName(FOREMANCC_TEST_SCRIPT_LOG_TRACE_METHOD));
  BOOST_CHECK(foremanTraceLogger->setCode(testLogTrace));
  BOOST_CHECK_MESSAGE(mgr.addMethod(foremanTraceLogger, &err), err);

#endif
  
  // run all tests

  testController.run(&mgr);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

#endif
