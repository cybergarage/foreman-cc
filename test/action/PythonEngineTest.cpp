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

#include <foreman/action/Script.h>
#include <foreman/action/impl/Python.h>

BOOST_AUTO_TEST_SUITE(action)
BOOST_AUTO_TEST_SUITE(python)

#if defined(FOREMAN_SUPPORT_PYTHON)

BOOST_AUTO_TEST_CASE(PythonEngine)
{
  PythonEngine* engine = new PythonEngine();
  delete engine;
}

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

  Foreman::Action::PythonParameters pyInParams;
  BOOST_CHECK(pyInParams.set(&params));
  BOOST_CHECK(pyInParams.equals(&params));

  Foreman::Action::Parameters pyOutParams;
  BOOST_CHECK(pyInParams.get(&params));
  BOOST_CHECK(pyInParams.equals(&pyOutParams));

  Py_Finalize();
}

#endif

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
