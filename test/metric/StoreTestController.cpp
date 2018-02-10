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

void StoreTestContoller::run(Foreman::Metric::MemStore* store)
{
  BOOST_CHECK(store->open());

  BOOST_CHECK_EQUAL(store->getRowCount(), 0);
  BOOST_CHECK_EQUAL(store->getColumnCount(), 0);

  // Initialize metrics

  Foreman::Metric::MetricArray metrics;
  for (size_t n = 0; n < FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT; n++) {
    std::ostringstream s;
    s << FORMANCC_MEMSTORETESTCONTROLLER_METRICS_NAME_PREFIX << n;
    auto m = std::shared_ptr<Foreman::Metric::Metric>(new Foreman::Metric::Metric());
    m->name = s.str();
    metrics.push_back(m);
  }

  // Initialize memstore

  BOOST_CHECK(store->setRetentionInterval(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL));
  BOOST_CHECK(store->setRetentionPeriod(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_SEC));
  BOOST_CHECK_EQUAL(store->getColumnCount(), FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT);

  // Add metric
  
  for (auto m : metrics) {
    store->addMetric(m);
  }
  
  BOOST_CHECK_EQUAL(store->getRowCount(), FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT);
  BOOST_CHECK(store->realloc());
  
  // Query metric
  
  for (auto m : metrics) {
    Foreman::Metric::Query q;
    q.setTarget(*m);

    Foreman::Metric::ResultSet rs;
    
    BOOST_CHECK(store->queryMetric(&q, &rs));
    BOOST_CHECK_EQUAL(rs.getDataPointCount(), 1);
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
    BOOST_CHECK_EQUAL(rs.getDataPointCount(), 1);

    for (Foreman::Metric::Metrics* dps = rs.firstDataPoint(); dps; dps = rs.nextDataPoint()) {
      size_t dpsCount = dps->size();
      BOOST_CHECK_EQUAL(dpsCount, FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT);
      for (size_t n = 0; n < dpsCount; n++) {
        Foreman::Metric::DataPoint* dp = dps->getDataPoint(n);
        if (dp->getValue() != n)
          BOOST_CHECK_EQUAL(dp->getValue(), n);
      }
    }
  }

  BOOST_CHECK(store->close());
}
