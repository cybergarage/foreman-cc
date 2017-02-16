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

// using namespace Foreman::Test;

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

  BOOST_CHECK(store->setRetentionInterval(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL));
  BOOST_CHECK(store->setRetentionPeriod(FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_SEC));

  for (size_t n = 0; n < FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT; n++) {
    Foreman::Metric m;
    store->addMetric(m);
  }
  BOOST_CHECK(store->realloc());

  BOOST_CHECK(store->close());
}
