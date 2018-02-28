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

#include "StoreTestController.h"

using namespace Foreman::Metric;

////////////////////////////////////////////////
// StoreTestContoller
////////////////////////////////////////////////

StoreTestContoller::StoreTestContoller() {}

StoreTestContoller::~StoreTestContoller() {}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

void StoreTestContoller::run(Foreman::Metric::Store* store)
{
  auto memStore = dynamic_cast<Foreman::Metric::MemStore*>(store);
  auto sqlStore = dynamic_cast<Foreman::Metric::SQLiteStore*>(store);

  BOOST_CHECK(store->open());

  if (memStore) {
    BOOST_CHECK_EQUAL(memStore->getRowCount(), 0);
    BOOST_CHECK_EQUAL(memStore->getColumnCount(), 0);
  }

  // Initialize metrics

  Foreman::Metric::MetricArray metrics;
  for (size_t n = 0; n < FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT; n++) {
    std::ostringstream s;
    s << FORMANCC_MEMSTORETESTCONTROLLER_METRICS_NAME_PREFIX << n;
    auto m = std::shared_ptr<Foreman::Metric::Metric>(new Foreman::Metric::Metric());
    m->name = s.str();
    metrics.push_back(m);
  }

  // Initialize store

  BOOST_CHECK(store->setRetentionInterval(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL));
  BOOST_CHECK(store->setRetentionPeriod(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_SEC));

  if (memStore) {
    BOOST_CHECK_EQUAL(memStore->getColumnCount(), FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT);
  }

  // Add metric

  for (auto m : metrics) {
    store->addMetric(m);
  }

  if (memStore) {
    BOOST_CHECK_EQUAL(memStore->getRowCount(), FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT);
    BOOST_CHECK(memStore->realloc());
  }

  // Query metric

  for (auto m : metrics) {
    Foreman::Metric::Query q;
    q.setTarget(*m);

    Foreman::Metric::ResultSet rs;

    BOOST_CHECK(store->queryMetric(&q, &rs));
    BOOST_CHECK_EQUAL(rs.getMetricsCount(), 1);
  }

  // Query metric (LIKE)

  if (sqlStore) { // TODO: All store should support like search
    Foreman::Metric::Query q;
    q.setTarget(FORMANCC_MEMSTORETESTCONTROLLER_METRICS_NAME_PREFIX "*");

    Foreman::Metric::ResultSet rs;
    BOOST_CHECK(store->queryMetric(&q, &rs));
    BOOST_CHECK_EQUAL(rs.getMetricsCount(), FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT);
  }

  // Insert metrics data

  time_t beginTs = time(NULL);
  time_t metricTs = beginTs;
  for (size_t n = 0; n < FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT; n++) {
    Foreman::Metric::MetricArray values;
    for (auto m : metrics) {
      auto value = std::shared_ptr<Foreman::Metric::Metric>(new Foreman::Metric::Metric(*m));
      value->timestamp = metricTs;
      value->value = n;
      values.push_back(value);
    }
    BOOST_CHECK(store->addData(values));
    metricTs += FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL;
  }
  time_t endTs = metricTs;

  // Get metrics data

  for (auto m : metrics) {
    Foreman::Metric::Query q;
    q.setTarget(*m);
    q.setFrom(beginTs);
    q.setUntil(endTs);
    q.setInterval(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL);

    Foreman::Metric::ResultSet rs;

    BOOST_CHECK(store->queryData(&q, &rs));
    BOOST_CHECK_EQUAL(rs.getMetricsCount(), 1);

    for (auto m = rs.firstMetrics(); m; m = rs.nextMetrics()) {
      size_t mCount = m->size();
      BOOST_CHECK_EQUAL(mCount, FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT);
      for (size_t n = 0; n < mCount; n++) {
        auto dp = m->getDataPoint(n);
        if (dp->getValue() != n) {
          BOOST_CHECK_EQUAL(dp->getValue(), n);
        }
      }
    }
  }

  // Analyze metrics data

#if defined(FOREMAN_ENABLE_ANALYZER)

  if (sqlStore) { // TODO: All store should support like search
    for (auto m : metrics) {
      Foreman::Metric::Query q;
      q.setTarget(*m);
      q.setFrom(beginTs);
      q.setUntil(endTs);
      q.setInterval(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL);

      Foreman::Metric::ResultSet rs;

      BOOST_CHECK(store->analyzeData(&q, &rs));
      BOOST_CHECK_EQUAL(rs.getMetricsCount(), FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT);

      for (auto m = rs.firstMetrics(); m; m = rs.nextMetrics()) {
        size_t mCount = m->size();
        BOOST_CHECK_EQUAL(mCount, 1);
        if (mCount < 1)
          continue;
        auto dp = m->getDataPoint(0);
        BOOST_CHECK(0 <= dp->getValue());
      }
      
      // NOTE : Check only first metrics
      break;
    }
  }

#endif

  // Finalize

  BOOST_CHECK(store->close());
}
