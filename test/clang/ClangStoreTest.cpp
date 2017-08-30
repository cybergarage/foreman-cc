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

/*

typedef void ForemanMetric;

ForemanMetric* foreman_metric_new();

bool foreman_metric_setname(ForemanMetric* m, const char* name);
bool foreman_metric_setvalue(ForemanMetric* m, double value);
bool foreman_metric_settimestamp(ForemanMetric* m, time_t ts);

bool foreman_metric_getname(ForemanMetric* m, const char** name);
bool foreman_metric_getvalue(ForemanMetric* m, double* value);
bool foreman_metric_gettimestamp(ForemanMetric* m, time_t* ts);

bool foreman_metric_delete(ForemanMetric* m);


typedef void ForemanQuery;

ForemanQuery* foreman_query_new();

bool foreman_query_settarget(ForemanQuery* q, const char* name);
bool foreman_query_setfrom(ForemanQuery* q, time_t ts);
bool foreman_query_setuntil(ForemanQuery* q, time_t ts);
bool foreman_query_setinterval(ForemanQuery* q, time_t ts);

bool foreman_query_gettarget(ForemanQuery* q, const char** name);
bool foreman_query_getfrom(ForemanQuery* q, time_t* ts);
bool foreman_query_getuntil(ForemanQuery* q, time_t* ts);
bool foreman_query_getinterval(ForemanQuery* q, time_t* ts);

bool foreman_query_delete(ForemanQuery* q);

typedef void ForemanResultSet;

ForemanResultSet* foreman_resultset_new();

size_t foreman_resultset_getcount(ForemanResultSet* q);
double* foreman_resultset_getvalues(ForemanResultSet* q);

bool foreman_resultset_delete(ForemanResultSet* q);


typedef void ForemanStore;

ForemanStore* foreman_store_matrix_create();
ForemanStore* foreman_store_ringmap_create();
ForemanStore* foreman_store_sqlite_create();
ForemanStore* foreman_store_tsmap_create();

bool foreman_store_delete(ForemanStore* store);

bool foreman_store_open(ForemanStore* store);
bool foreman_store_close(ForemanStore* store);

bool foreman_store_addmetric(ForemanStore* store, ForemanMetric* m);
bool foreman_store_query(ForemanStore* store, ForemanQuery* q, ForemanResultSet* rs);

*/
