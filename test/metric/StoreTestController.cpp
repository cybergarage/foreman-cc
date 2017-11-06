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

#include "StoreTestController.h"

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

  Foreman::Metric::Metrics metrics;
  for (size_t n = 0; n < FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT; n++) {
    std::ostringstream s;
    s << FORMANCC_MEMSTORETESTCONTROLLER_METRICS_NAME_PREFIX << n;
    std::shared_ptr<Foreman::Metric::Metric> m = std::shared_ptr<Foreman::Metric::Metric>(new Foreman::Metric::Metric());
    m->name = s.str();
    metrics.push_back(m);
  }

  // Initialize memstore

  BOOST_CHECK(store->setRetentionInterval(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL));
  BOOST_CHECK(store->setRetentionPeriod(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_SEC));
  BOOST_CHECK_EQUAL(store->getColumnCount(), FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT);

  for (std::shared_ptr<Foreman::Metric::Metric> m : metrics) {
    store->addMetric(m);
  }

  BOOST_CHECK_EQUAL(store->getRowCount(), FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT);
  BOOST_CHECK(store->realloc());

  // Insert metrics

  time_t beginTs = time(NULL);
  time_t metricTs = beginTs;
  for (size_t n = 0; n < FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT; n++) {
    Foreman::Metric::Metrics values;
    for (std::shared_ptr<Foreman::Metric::Metric> m : metrics) {
      std::shared_ptr<Foreman::Metric::Metric> value = std::shared_ptr<Foreman::Metric::Metric>(new Foreman::Metric::Metric(*m));
      value->timestamp = metricTs;
      value->value = n;
      values.push_back(value);
    }
    BOOST_CHECK(store->addValues(values));
    metricTs += FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL;
  }
  time_t endTs = metricTs;

  // Get metrics

  for (std::shared_ptr<Foreman::Metric::Metric> m : metrics) {
    Foreman::Metric::Query q;
    q.setTarget(*m);
    q.setFrom(beginTs);
    q.setUntil(endTs);
    q.setInterval(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL);

    Foreman::Metric::ResultSet rs;

    BOOST_CHECK(store->getValues(&q, &rs));
    BOOST_CHECK_EQUAL(rs.getDataPointCount(), 1);

    for (Foreman::Metric::DataPoints* dps = rs.firstDataPoint(); dps; dps = rs.nextDataPoint()) {
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
