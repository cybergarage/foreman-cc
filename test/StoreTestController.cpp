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

#include "MemStoreTestController.h"

////////////////////////////////////////////////
// MemStoreTestContoller
////////////////////////////////////////////////

MemStoreTestContoller::MemStoreTestContoller() {}

MemStoreTestContoller::~MemStoreTestContoller() {}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

void MemStoreTestContoller::run(Foreman::MemStore* store)
{
  BOOST_CHECK(store->open());

  BOOST_CHECK_EQUAL(store->getRowCount(), 0);
  BOOST_CHECK_EQUAL(store->getColumnCount(), 0);

  // Initialize metrics

  Foreman::Metrics metrics;
  for (size_t n = 0; n < FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT; n++) {
    std::ostringstream s;
    s << FORMANCC_MEMSTORETESTCONTROLLER_METRICS_NAME_PREFIX << n;
    std::shared_ptr<Foreman::Metric> m = std::shared_ptr<Foreman::Metric>(new Foreman::Metric());
    m->name = s.str();
    metrics.push_back(m);
  }

  // Initialize memstore

  BOOST_CHECK(store->setRetentionInterval(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL));
  BOOST_CHECK(store->setRetentionPeriod(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_SEC));
  BOOST_CHECK_EQUAL(store->getColumnCount(), FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT);

  for (std::shared_ptr<Foreman::Metric> m : metrics) {
    store->addMetric(m);
  }

  BOOST_CHECK_EQUAL(store->getRowCount(), FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT);
  BOOST_CHECK(store->realloc());

  // Insert metrics

  time_t beginTs = time(NULL);
  time_t metricTs = beginTs;
  for (size_t n = 0; n < FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT; n++) {
    Foreman::Metrics values;
    for (std::shared_ptr<Foreman::Metric> m : metrics) {
      std::shared_ptr<Foreman::Metric> value = std::shared_ptr<Foreman::Metric>(new Foreman::Metric(*m));
      value->timestamp = metricTs;
      value->value = n;
      values.push_back(value);
    }
    BOOST_CHECK(store->addValues(values));
    metricTs += FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL;
  }
  time_t endTs = metricTs;

  // Get metrics

  for (std::shared_ptr<Foreman::Metric> m : metrics) {
    std::shared_ptr<double> values = nullptr;
    Foreman::Query q;
    q.setTarget(*m);
    q.setFrom(beginTs);
    q.setUntil(endTs);
    q.setInterval(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL);

    Foreman::ResultSet rs;

    BOOST_CHECK(store->getValues(&q, &rs));
    BOOST_CHECK_EQUAL(rs.valueCount, FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT);
    for (size_t n = 0; n < rs.valueCount; n++) {
      BOOST_CHECK_EQUAL(rs.values[n], n);
    }
  }

  BOOST_CHECK(store->close());
}
