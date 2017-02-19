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
    store->addMetric(*m);
  }

  BOOST_CHECK_EQUAL(store->getRowCount(), FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT);
  BOOST_CHECK(store->realloc());

  // Insert metrics
  
  for (size_t n = 0; n < FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT; n++) {
    for (std::shared_ptr<Foreman::Metric> m : metrics) {
      store->addMetric(*m);
    }
  }

  BOOST_CHECK(store->close());
}
