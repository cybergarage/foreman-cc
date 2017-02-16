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
  BOOST_CHECK(store->close());
}
