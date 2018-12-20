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
  Foreman::Client client;
  
  if (!client.ping())
    return;
}
