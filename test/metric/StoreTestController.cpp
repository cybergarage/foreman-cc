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
Foreman:
  bool result;
  Error err;
  auto tsStore = dynamic_cast<Foreman::Metric::TimeSeriesMapStore*>(store);
  auto sqlStore = dynamic_cast<Foreman::Metric::SQLiteStore*>(store);

  BOOST_CHECK(store->open());

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

  // Add metric

  for (auto m : metrics) {
    store->addMetric(m);
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
  time_t endTs = beginTs + (FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL * FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT);

  // Analyze metrics data for empty store

#if defined(FOREMAN_ENABLE_ANALYZER)

  if (sqlStore) { // TODO: All store should support like search
    for (auto m : metrics) {
      Foreman::Metric::Query q;
      q.setTarget(*m);
      q.setFrom(beginTs);
      q.setUntil(endTs);
      q.setInterval(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL);

      Foreman::Metric::ResultSet rs;

      BOOST_CHECK(!store->analyzeData(&q, &rs, &err));

      // NOTE : Check only first metrics to save the testing time.
      if (m)
        break;
    }
  }

#endif

  // Insert metrics data

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
  endTs = metricTs;

  // Get metrics data

  for (auto m : metrics) {
    Foreman::Metric::Query q;
    q.setTarget(*m);
    q.setFrom(beginTs);
    q.setUntil(endTs);
    q.setInterval(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL);

    Foreman::Metric::ResultSet rs;

    result = store->queryData(&q, &rs);
    BOOST_CHECK(result);
    if (result) {
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

      BOOST_CHECK(store->analyzeData(&q, &rs, &err));
      BOOST_CHECK_EQUAL(rs.getMetricsCount(), FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT);

      for (auto m = rs.firstMetrics(); m; m = rs.nextMetrics()) {
        size_t mCount = m->size();
        BOOST_CHECK(2 <= mCount);
        if (mCount < 2)
          continue;
        auto corr = m->getDataPoint(0);
        BOOST_CHECK(0 <= corr->getValue());
        auto maxDp = m->getDataPoint(1);
        BOOST_CHECK(0 <= maxDp->getValue());
        BOOST_CHECK(0 <= maxDp->getTimestamp());
      }

      // NOTE : Check only first metrics to save the testing time.
      if (m)
        break;
    }
  }

#endif

  // Delete expired

  if (tsStore) {
    tsStore->clear();
    std::time_t now = std::time(nullptr);
    int i = 0, n;
    for (n = 0; n < FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT; n++) {
      Foreman::Metric::MetricArray values;
      for (auto m : metrics) {
        auto value = Foreman::Metric::Metric(*m);
        value.timestamp = now - i++;
        value.value = n;
        BOOST_CHECK(tsStore->addData(value));
      }
    }
    tsStore->setRetentionPeriod(i / 2);
    int del_count = tsStore->deleteExpiredMetrics();
    BOOST_CHECK_EQUAL(n, i / 2 + del_count);
  }

  // Finalize

  BOOST_CHECK(store->close());
}
