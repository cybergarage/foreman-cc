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
#include <foreman/action/impl/Python.h>

#if defined(FOREMAN_SUPPORT_PYTHON)

BOOST_AUTO_TEST_SUITE(action)
BOOST_AUTO_TEST_SUITE(python)

BOOST_AUTO_TEST_CASE(PythonParameters)
{
  Py_Initialize();

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

  Py_Finalize();
}

BOOST_AUTO_TEST_CASE(PythonEngine)
{
  Foreman::Error err;
  Foreman::Action::Manager mgr;
  Foreman::Action::ManagerTestController testControllerr;

  // hello

  static const char* PY_ECHO_CODE = "def " FOREMANCC_SCRIPT_ECHO_METHOD "(params,results):\n"
                                    "  for key, value in params.iteritems():\n"
                                    "    results[key] = value\n"
                                    "  return True\n";

  auto hello = new Foreman::Action::PythonMethod();
  BOOST_CHECK(hello->setName(FOREMANCC_SCRIPT_ECHO_METHOD));
  BOOST_CHECK(hello->setCode(PY_ECHO_CODE));
  BOOST_CHECK(mgr.addMethod(hello, &err));

  // set_registry

  static const char* PY_SET_REGISTRY_CODE = "import " FOREMANCC_PRODUCT_NAME "\n"
                                            "def " FOREMANCC_SCRIPT_SET_REGISTER_METHOD "(params,results):\n"
                                            "  for key, value in params.iteritems():\n"
                                            "    " FOREMANCC_PRODUCT_NAME "." FOREMANCC_PYTHON_SETREGISTER "(key, value)\n"
                                            "  return True\n";

  auto setreg = new Foreman::Action::PythonMethod();
  BOOST_CHECK(setreg->setName(FOREMANCC_SCRIPT_SET_REGISTER_METHOD));
  BOOST_CHECK(setreg->setCode(PY_SET_REGISTRY_CODE));
  BOOST_CHECK(mgr.addMethod(setreg, &err));

  // get_registry

  static const char* PY_GET_REGISTRY_CODE = "import " FOREMANCC_PRODUCT_NAME "\n"
                                            "def " FOREMANCC_SCRIPT_GET_REGISTER_METHOD "(params,results):\n"
                                            "  for reg_key, value in params.iteritems():\n"
                                            "    reg_value = " FOREMANCC_PRODUCT_NAME "." FOREMANCC_PYTHON_GETREGISTER "(reg_key)\n"
                                            "    results[reg_key] = reg_value\n"
                                            "  return True\n";

  auto getreg = new Foreman::Action::PythonMethod();
  BOOST_CHECK(getreg->setName(FOREMANCC_SCRIPT_GET_REGISTER_METHOD));
  BOOST_CHECK(getreg->setCode(PY_GET_REGISTRY_CODE));
  BOOST_CHECK(mgr.addMethod(getreg, &err));

  // remove_registry

  static const char* PY_REMOVE_REGISTRY_CODE = "import " FOREMANCC_PRODUCT_NAME "\n"
                                               "def " FOREMANCC_SCRIPT_REMOVE_REGISTER_METHOD "(params,results):\n"
                                               "  for key, value in params.iteritems():\n"
                                               "    if " FOREMANCC_PRODUCT_NAME "." FOREMANCC_PYTHON_REMOVEREGISTER "(key) == False:\n"
                                               "      return False\n"
                                               "  return True\n";

  auto rmreg = new Foreman::Action::PythonMethod();
  BOOST_CHECK(rmreg->setName(FOREMANCC_SCRIPT_REMOVE_REGISTER_METHOD));
  BOOST_CHECK(rmreg->setCode(PY_REMOVE_REGISTRY_CODE));
  BOOST_CHECK(mgr.addMethod(rmreg, &err));

  testControllerr.run(&mgr);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

#endif
