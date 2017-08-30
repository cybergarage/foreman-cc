/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <foreman/foreman-c.h>

#include "../ForemanTest.h"

using namespace Foreman;

BOOST_AUTO_TEST_SUITE(clang)

static void TestClangStore(ForemanStore *store) {
  BOOST_CHECK(foreman_store_open(store));
  
  ForemanMetric *m[FORMANCC_TEST_LOOP_DEFAULT];
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
    BOOST_CHECK(foreman_store_addmetric(store, m[n]));
  }
  
  // Query metric values

  ForemanQuery *q = foreman_query_new();
  BOOST_CHECK(foreman_query_setfrom(q, from));
  BOOST_CHECK(foreman_query_setuntil(q, until));
  BOOST_CHECK(foreman_query_setinterval(q, interval));
  for (n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    const char *mname;
    BOOST_CHECK(foreman_metric_getname(m[n], &mname));
    BOOST_CHECK(foreman_query_settarget(q, mname));
    
    ForemanResultSet *rs = foreman_resultset_new();
    BOOST_CHECK(foreman_store_query(store, q, rs));
    
    BOOST_CHECK_EQUAL(foreman_resultset_getcount(rs), 1);
    double rsValue;
    BOOST_CHECK(foreman_resultset_getvalue(rs, 0, &rsValue));
    BOOST_CHECK_EQUAL((int)rsValue, n);
    
    BOOST_CHECK(foreman_resultset_delete(rs));
  }
              
  for (n = 0; n < FORMANCC_TEST_LOOP_DEFAULT; n++) {
    BOOST_CHECK(foreman_metric_delete(m[n]));
  }
  
  BOOST_CHECK(foreman_store_close(store));
}

BOOST_AUTO_TEST_CASE(ClangStore)
{
  TestClangStore(foreman_store_sqlite_create());
}

BOOST_AUTO_TEST_SUITE_END()
