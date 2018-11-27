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
#include <math.h>

#include <foreman/foreman-c.h>

#include "../../../ForemanTest.h"
#include "ClangMetricStoreConfig.h"

using namespace Foreman;

BOOST_AUTO_TEST_SUITE(clang)

static void TestClangStore(ForemanMetricStore* store, ClangMetricsStoreTestConfig* config)
{
  BOOST_CHECK(foreman_metric_store_setretentionperiod(store, config->retentionPeriod));
  BOOST_CHECK(foreman_metric_store_setretentioninterval(store, config->retentionInterval));

  BOOST_CHECK(foreman_metric_store_open(store));

  // Initialize metrics

  ForemanMetric* m[config->metricsCount];
  char name[32];
  int n;

  for (n = 0; n < config->metricsCount; n++) {
    m[n] = foreman_metric_new();
    BOOST_CHECK(m[n]);
    snprintf(name, sizeof(name), "%s%04d", FORMANCC_STORETESTCONTROLLER_METRICS_NAME_PREFIX, n);
    BOOST_CHECK(foreman_metric_setname(m[n], name));
  }

  // Base timestamps

  time_t now = time(NULL);
  time_t from = now - (now % config->retentionInterval);
  time_t until = from + config->retentionPeriod;

  // Insert metric values

  int tn;
  time_t ts = from;
  for (tn = 0; tn < (config->retentionPeriod / config->insertInterval); tn++) {
    int mvalue = tn / (config->retentionInterval / config->insertInterval);
    time_t mts = ts;
    if (config->enableTimestampJitter) {
      mts += rand() % config->insertInterval;
    }
    for (n = 0; n < config->metricsCount; n++) {
      const char* mname;
      BOOST_CHECK(foreman_metric_getname(m[n], &mname));
      BOOST_CHECK(foreman_metric_settimestamp(m[n], mts));
      BOOST_CHECK(foreman_metric_setvalue(m[n], (double)(mvalue)));
      BOOST_CHECK(foreman_metric_store_addmetric(store, m[n]));
      BOOST_TEST_MESSAGE("I : " << mname << "[" << mts << "] : " << mvalue);
    }
    ts += config->insertInterval;
  }

  // Query metrics
  
  auto q = foreman_metric_query_new();
  for (n = 0; n < config->metricsCount; n++) {
    const char* mname;
    BOOST_CHECK(foreman_metric_getname(m[n], &mname));
    BOOST_CHECK(foreman_metric_query_settarget(q, mname));
    
    auto rs = foreman_metric_resultset_new();
    BOOST_CHECK(foreman_metric_store_querymetric(store, q, rs));
    
    BOOST_CHECK_EQUAL(foreman_metric_resultset_getdatapointcount(rs), 1);
    auto qm = foreman_metric_resultset_getfirstmetrics(rs);
    BOOST_CHECK(qm);
    
    const char* qname;
    BOOST_CHECK(foreman_metric_getname(qm, &qname));
    // FIXME
    //BOOST_CHECK_EQUAL(qname, mname);
    
    BOOST_CHECK(foreman_metric_resultset_delete(rs));
  }
  
  // Query metric values

  q = foreman_metric_query_new();
  BOOST_CHECK(foreman_metric_query_setfrom(q, from));
  BOOST_CHECK(foreman_metric_query_setuntil(q, until));
  BOOST_CHECK(foreman_metric_query_setinterval(q, config->retentionInterval));

  for (n = 0; n < config->metricsCount; n++) {
    const char* mname;
    BOOST_CHECK(foreman_metric_getname(m[n], &mname));
    BOOST_CHECK(foreman_metric_query_settarget(q, mname));

    auto rs = foreman_metric_resultset_new();
    BOOST_CHECK(foreman_metric_store_querydata(store, q, rs));

    BOOST_CHECK_EQUAL(foreman_metric_resultset_getdatapointcount(rs), 1);
    auto m = foreman_metric_resultset_findmetrics(rs, mname);
    BOOST_CHECK(m);

    size_t dataCnt = foreman_metric_metrics_getdatapointsize(m);
    BOOST_CHECK_EQUAL(dataCnt, (config->retentionPeriod / config->retentionInterval));

    for (auto i = 0; i < dataCnt; i++) {
      auto dp = foreman_metric_metrics_getdatapoint(m, i);
      BOOST_CHECK(dp);
      if (!dp)
        continue;
      time_t dpTs = foreman_metric_datapoint_gettimestamp(dp);
      double dpValue = foreman_metric_datapoint_getvalue(dp);
      BOOST_TEST_MESSAGE("S : " << mname << "[" << dpTs << "] : " << dpValue);
      BOOST_CHECK_EQUAL(dpTs, (from + (config->retentionInterval * i)));
      BOOST_CHECK_EQUAL((int)dpValue, i);
    }
    BOOST_CHECK(foreman_metric_resultset_delete(rs));
  }

  for (n = 0; n < config->metricsCount; n++) {
    BOOST_CHECK(foreman_metric_delete(m[n]));
  }

  BOOST_CHECK(foreman_metric_store_close(store));
}

BOOST_AUTO_TEST_CASE(ClangSQLiteStore)
{
  ClangMetricsStoreTestConfig config;
  config.retentionPeriod = 60 * 60 * 3;
  config.retentionInterval = 60 * 5;
  config.insertInterval = 60;

  TestClangStore(foreman_metric_store_sqlite_create(), &config);
}

BOOST_AUTO_TEST_CASE(ClangSQLiteStoreWithTimestampJitter)
{
  ClangMetricsStoreTestConfig config;
  config.retentionPeriod = 60 * 60 * 3;
  config.retentionInterval = 60 * 5;
  config.insertInterval = 60;
  config.enableTimestampJitter = true;

  TestClangStore(foreman_metric_store_sqlite_create(), &config);
}

BOOST_AUTO_TEST_SUITE_END()
