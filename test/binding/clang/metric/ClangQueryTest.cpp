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

#include <foreman/foreman-c.h>

#include "../../../ForemanTest.h"

using namespace Foreman;

BOOST_AUTO_TEST_SUITE(clang)

BOOST_AUTO_TEST_CASE(ClangMetricQuery)
{
  char nameBuf[32];
  const char* name;
  time_t ts;

  for (size_t n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    ForemanMetricQuery* q = foreman_metric_query_new();
    BOOST_CHECK(q);

    snprintf(nameBuf, sizeof(nameBuf), "name%ld", n);
    BOOST_CHECK(foreman_metric_query_settarget(q, nameBuf));
    BOOST_CHECK(foreman_metric_query_gettarget(q, &name));
    BOOST_CHECK_EQUAL(nameBuf, name);

    BOOST_CHECK(foreman_metric_query_setfrom(q, (time_t)n));
    BOOST_CHECK(foreman_metric_query_getfrom(q, &ts));
    BOOST_CHECK_EQUAL((time_t)n, ts);

    BOOST_CHECK(foreman_metric_query_setuntil(q, (time_t)(n + 1000)));
    BOOST_CHECK(foreman_metric_query_getuntil(q, &ts));
    BOOST_CHECK_EQUAL((time_t)(n + 1000), ts);

    BOOST_CHECK(foreman_metric_query_setinterval(q, (time_t)(n + 2000)));
    BOOST_CHECK(foreman_metric_query_getinterval(q, &ts));
    BOOST_CHECK_EQUAL((time_t)(n + 2000), ts);

    BOOST_CHECK(foreman_metric_query_delete(q));
  }
}

BOOST_AUTO_TEST_SUITE_END()
