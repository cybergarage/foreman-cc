/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#define BOOST_TEST_MODULE ForemanTest
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/random.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>

#include "ForemanTest.h"

/****************************************
 * ForemanFixture
 ****************************************/

struct ForemanFixture {
  ForemanFixture() { Foreman::Test::Setup(); }

  ~ForemanFixture() {}
};

BOOST_GLOBAL_FIXTURE(ForemanFixture);

/****************************************
 * Setup
 ****************************************/

void Foreman::Test::Setup() {}
