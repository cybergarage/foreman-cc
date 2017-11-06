/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <foreman/foreman-c.h>

#include "../../ForemanTest.h"

using namespace Foreman;

BOOST_AUTO_TEST_SUITE(clang)

BOOST_AUTO_TEST_CASE(ClangMetric)
{
  char nameBuf[32];
  const char* name;
  double value;
  time_t ts;

  for (size_t n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    ForemanMetric* m = foreman_metric_new();
    BOOST_CHECK(m);

    snprintf(nameBuf, sizeof(nameBuf), "name%ld", n);
    BOOST_CHECK(foreman_metric_setname(m, nameBuf));
    BOOST_CHECK(foreman_metric_getname(m, &name));
    BOOST_CHECK_EQUAL(nameBuf, name);

    BOOST_CHECK(foreman_metric_setvalue(m, (double)n));
    BOOST_CHECK(foreman_metric_getvalue(m, &value));
    BOOST_CHECK_EQUAL(n, (size_t)value);

    BOOST_CHECK(foreman_metric_settimestamp(m, (time_t)n));
    BOOST_CHECK(foreman_metric_gettimestamp(m, &ts));
    BOOST_CHECK_EQUAL((time_t)n, ts);

    BOOST_CHECK(foreman_metric_delete(m));
  }
}

BOOST_AUTO_TEST_SUITE_END()
