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
#include <stdio.h>

#include <foreman/registry/Object.h>

#include "../ForemanTest.h"

using namespace Foreman::Registry;

BOOST_AUTO_TEST_SUITE(registry)

BOOST_AUTO_TEST_CASE(ObjectProperty)
{
  Object obj;
  Properties props;

  char pname[FORMANCC_TEST_LOOP_DEFAULT][32];
  char pdata[FORMANCC_TEST_LOOP_DEFAULT][32];

  BOOST_CHECK_EQUAL(props.size(), 0);
  for (size_t n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    snprintf(pname[n], sizeof(pname), "pname%ld", n);
    snprintf(pdata[n], sizeof(pdata), "pdata%ld", n);
  }

  // Insert

  for (size_t n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    Property prop;
    prop.setName(pname[n]);
    prop.setData(pdata[n]);
    BOOST_CHECK(obj.setProperty(&prop));
  }

  // Get

  props.clear();
  BOOST_CHECK(obj.getProperties(&props));
  BOOST_CHECK_EQUAL(props.size(), FORMANCC_TEST_LOOP_DEFAULT);
  for (size_t n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    Property* prop = props.getProperty(n);
    BOOST_CHECK(prop);
    BOOST_CHECK_EQUAL(prop->getName(), pname[n]);
    BOOST_CHECK_EQUAL(prop->getData(), pdata[n]);
  }

  // Insert (Dupulicated)

  for (size_t n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    snprintf(pdata[n], sizeof(pdata), "new_pdata%ld", n);
  }

  for (size_t n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    Property prop;
    prop.setName(pname[n]);
    prop.setData(pdata[n]);
    BOOST_CHECK(obj.setProperty(&prop));
  }

  // Get

  props.clear();
  BOOST_CHECK(obj.getProperties(&props));
  BOOST_CHECK_EQUAL(props.size(), FORMANCC_TEST_LOOP_DEFAULT);
  for (size_t n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    Property* prop = props.getProperty(n);
    BOOST_CHECK(prop);
    BOOST_CHECK_EQUAL(prop->getName(), pname[n]);
    BOOST_CHECK_EQUAL(prop->getData(), pdata[n]);
  }
}

BOOST_AUTO_TEST_SUITE_END()
