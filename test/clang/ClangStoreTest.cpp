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

#include "../ForemanTest.h"

using namespace Foreman;

BOOST_AUTO_TEST_SUITE(clang)

static void TestClangStore(ForemanMetricStore* store)
{
  BOOST_CHECK(foreman_metric_store_open(store));

  ForemanMetric* m[FORMANCC_TEST_LOOP_DEFAULT];
  char name[32];
  int n;

  for (n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    m[n] = foreman_metric_new();
    BOOST_CHECK(m[n]);
    snprintf(name, sizeof(name), "path%d", n);
    BOOST_CHECK(foreman_metric_setname(m[n], name));
  }

  time_t from = time(NULL);
  time_t interval = 5 * 60; /* sec */
  time_t until = from + interval;

  // Insert metric values

  for (n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    BOOST_CHECK(foreman_metric_settimestamp(m[n], from));
    BOOST_CHECK(foreman_metric_setvalue(m[n], (double)n));
    BOOST_CHECK(foreman_metric_store_addmetric(store, m[n]));
  }

  // Query metric values

  ForemanMetricQuery* q = foreman_metric_query_new();
  BOOST_CHECK(foreman_metric_query_setfrom(q, from));
  BOOST_CHECK(foreman_metric_query_setuntil(q, until));
  BOOST_CHECK(foreman_metric_query_setinterval(q, interval));
  for (n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    const char* mname;
    BOOST_CHECK(foreman_metric_getname(m[n], &mname));
    BOOST_CHECK(foreman_metric_query_settarget(q, mname));

    ForemanMetricResultSet* rs = foreman_metric_resultset_new();
    BOOST_CHECK(foreman_metric_store_query(store, q, rs));

    BOOST_CHECK_EQUAL(foreman_metric_resultset_getdatapointcount(rs), 1);
    ForemanMetricDataPoints* dps = foreman_metric_resultset_finddatapoints(rs, mname);
    BOOST_CHECK(dps);

    BOOST_CHECK_EQUAL(foreman_metric_datapoints_size(dps), 1);
    ForemanMetricDataPoints* dp = foreman_metric_datapoints_get(dps, 0);
    double rsValue = foreman_metric_datapoint_getvalue(dp);
    BOOST_CHECK_EQUAL((int)rsValue, n);

    BOOST_CHECK(foreman_metric_resultset_delete(rs));
  }

  for (n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    BOOST_CHECK(foreman_metric_delete(m[n]));
  }

  BOOST_CHECK(foreman_metric_store_close(store));
}

BOOST_AUTO_TEST_CASE(ClangStore)
{
  TestClangStore(foreman_metric_store_sqlite_create());
}

BOOST_AUTO_TEST_SUITE_END()
