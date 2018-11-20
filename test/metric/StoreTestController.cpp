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

StoreTestContoller::StoreTestContoller(StoreTestContollerConfig config)
{
  this->config = config;
}

StoreTestContoller::~StoreTestContoller() {}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

void StoreTestContoller::runInitializeTest(Foreman::Metric::Store* store)
{
  // Initialize timestamps

  auto now = time(NULL);
  this->testMetricBeginTs = now - (now % this->config.retentionInterval);
  this->testMetricEndTs = this->testMetricBeginTs + (this->config.retentionInterval * (this->config.retentionPeriod / this->config.retentionInterval));

  // Initialize store

  BOOST_CHECK(store->setRetentionInterval(this->config.retentionInterval));
  BOOST_CHECK(store->setRetentionPeriod(this->config.retentionPeriod));

  // Initialize metrics

  this->testMetrics.clear();

  for (size_t n = 0; n < this->config.metricsCount; n++) {
    std::ostringstream s;
    s << FORMANCC_STORETESTCONTROLLER_METRICS_NAME_PREFIX << n;
    auto m = std::shared_ptr<Foreman::Metric::Metric>(new Foreman::Metric::Metric());
    m->name = s.str();
    this->testMetrics.push_back(m);
  }
}

void StoreTestContoller::runInsertMetricsTest(Foreman::Metric::Store* store)
{
  // Add metric

  for (auto m : this->testMetrics) {
    store->addMetric(m);
  }
}

void StoreTestContoller::runQueryMetricsTest(Foreman::Metric::Store* store)
{
  auto sqlStore = dynamic_cast<Foreman::Metric::SQLiteStore*>(store);

  // Query metric

  for (auto m : this->testMetrics) {
    Foreman::Metric::Query q;
    q.setTarget(*m);

    Foreman::Metric::ResultSet rs;

    BOOST_CHECK(store->queryMetric(&q, &rs));
    BOOST_CHECK_EQUAL(rs.getMetricsCount(), 1);
  }

  // Query metric (LIKE)

  if (sqlStore) { // TODO: All store should support like search
    Foreman::Metric::Query q;
    q.setTarget(FORMANCC_STORETESTCONTROLLER_METRICS_NAME_PREFIX "*");

    Foreman::Metric::ResultSet rs;
    BOOST_CHECK(store->queryMetric(&q, &rs));
    BOOST_CHECK_EQUAL(rs.getMetricsCount(), this->config.metricsCount);
  }
}

void StoreTestContoller::runInsertMetricsDataTest(Foreman::Metric::Store* store)
{
  time_t metricTs = this->testMetricBeginTs;

  // Insert metrics data

  for (size_t n = 0; n < (this->config.retentionPeriod / this->config.insertInterval); n++) {
    Foreman::Metric::MetricArray values;
    for (auto m : this->testMetrics) {
      auto value = std::shared_ptr<Foreman::Metric::Metric>(new Foreman::Metric::Metric(*m));
      value->timestamp = metricTs;
      value->value = n;
      values.push_back(value);
    }
    BOOST_CHECK(store->addData(values));
    metricTs += this->config.insertInterval;
  }
}

void StoreTestContoller::runQueryMetricsDataTest(Foreman::Metric::Store* store)
{
  // Get metrics data

  for (auto m : this->testMetrics) {
    Foreman::Metric::Query q;
    q.setTarget(*m);
    q.setFrom(this->testMetricBeginTs);
    q.setUntil(this->testMetricEndTs);
    q.setInterval(this->config.retentionInterval);

    Foreman::Metric::ResultSet rs;

    auto result = store->queryData(&q, &rs);
    BOOST_CHECK(result);
    if (result) {
      BOOST_CHECK_EQUAL(rs.getMetricsCount(), 1);

      for (auto m = rs.firstMetrics(); m; m = rs.nextMetrics()) {
        size_t mCount = m->size();
        BOOST_CHECK_EQUAL(mCount, (this->config.retentionPeriod / this->config.retentionInterval));
        for (size_t n = 0; n < mCount; n++) {
          auto dp = m->getDataPoint(n);
          if (dp->getValue() != n) {
            BOOST_CHECK_EQUAL(dp->getValue(), n);
          }
        }
      }
    }
  }
}

void StoreTestContoller::runAllTests(Foreman::Metric::Store* store)
{
  Error err;
  auto tsStore = dynamic_cast<Foreman::Metric::TimeSeriesMapStore*>(store);
  auto sqlStore = dynamic_cast<Foreman::Metric::SQLiteStore*>(store);

  BOOST_CHECK(store->open());

  // Initialize store and metrics

  runInitializeTest(store);

  // Inesert and query metrics

  runInsertMetricsTest(store);
  runQueryMetricsTest(store);

  // Analyze metrics data for empty store

#if defined(FOREMAN_ENABLE_ANALYZER)

  if (sqlStore) { // TODO: All store should support like search
    for (auto m : this->testMetrics) {
      Foreman::Metric::Query q;
      q.setTarget(*m);
      q.setFrom(this->testMetricBeginTs);
      q.setUntil(this->testMetricEndTs);
      q.setInterval(this->config.retentionInterval);

      Foreman::Metric::ResultSet rs;

      BOOST_CHECK(!store->analyzeData(&q, &rs, &err));

      // NOTE : Check only first metrics to save the testing time.
      if (m)
        break;
    }
  }

#endif

  // Insert and query metrics data

  runInsertMetricsDataTest(store);
  runQueryMetricsDataTest(store);

  // Analyze metrics data

#if defined(FOREMAN_ENABLE_ANALYZER)

  if (sqlStore) { // TODO: All store should support like search
    for (auto m : this->testMetrics) {
      Foreman::Metric::Query q;
      q.setTarget(*m);
      q.setFrom(this->testMetricBeginTs);
      q.setUntil(this->testMetricEndTs);
      q.setInterval(this->config.retentionInterval);

      Foreman::Metric::ResultSet rs;

      BOOST_CHECK(store->analyzeData(&q, &rs, &err));
      BOOST_CHECK_EQUAL(rs.getMetricsCount(), this->config.metricsCount);

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
    for (n = 0; n < (this->config.retentionPeriod / this->config.retentionInterval); n++) {
      Foreman::Metric::MetricArray values;
      for (auto m : this->testMetrics) {
        auto value = Foreman::Metric::Metric(*m);
        value.timestamp = now - i++;
        value.value = n;
        BOOST_CHECK(tsStore->addData(value));
      }
    }
    tsStore->setRetentionPeriod(i / 2);
    auto del_count = tsStore->deleteExpiredMetrics();
    BOOST_CHECK_EQUAL(n, i / 2 + del_count);
  }

  // Finalize

  BOOST_CHECK(store->close());
}

void StoreTestContoller::runOnlyInsertTests(Foreman::Metric::Store* store)
{
  BOOST_CHECK(store->open());

  runInitializeTest(store);
  runInsertMetricsTest(store);
  runInsertMetricsDataTest(store);

  BOOST_CHECK(store->close());
}
