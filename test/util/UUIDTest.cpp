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

#include <foreman/util/UUID.h>

using namespace Foreman;

BOOST_AUTO_TEST_SUITE(util)

BOOST_AUTO_TEST_CASE(UUIDCreate)
{
  std::string uuid;
  BOOST_CHECK(CreateUUID(uuid));
}

BOOST_AUTO_TEST_SUITE_END()
