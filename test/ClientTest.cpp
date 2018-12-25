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

#include <foreman/Client.h>

BOOST_AUTO_TEST_CASE(Client)
{
  const char queries[][256] = {
    "EXPORT CONFIG"
  };
  
  Foreman::Client client;

  // Check whether foremand is runnging
  if (!client.ping())
    return;
  
  for(auto query : queries) {
    std::string res;
    BOOST_CHECK(client.query(query, &res));
    BOOST_CHECK(0 < res.size());
  }
}
