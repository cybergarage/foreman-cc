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

  BOOST_CHECK(store->setRetentionInterval(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL));
  BOOST_CHECK(store->setRetentionPeriod(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_SEC));
  BOOST_CHECK_EQUAL(store->getColumnCount(), (FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_SEC / FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL));

  for (size_t n = 0; n < FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT; n++) {
    std::ostringstream s;
    s << FORMANCC_MEMSTORETESTCONTROLLER_METRICS_NAME_PREFIX << n;
    Foreman::Metric m;
    m.name = s.str();
    store->addMetric(m);
  }
  BOOST_CHECK_EQUAL(store->getRowCount(), FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT);

  BOOST_CHECK(store->realloc());

  BOOST_CHECK(store->close());
}
