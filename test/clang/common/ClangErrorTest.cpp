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
#include <math.h>

#include <foreman/foreman-c.h>

BOOST_AUTO_TEST_SUITE(clang)

BOOST_AUTO_TEST_CASE(ErroDetailSetterTest)
{
  ForemanError* err;
  char msg[32], dmsg[32];
  int code, dcode;
  const char *rmsg, *rdmsg;
  int rcode, rdcode;

  err = foreman_error_new();
  BOOST_CHECK(err);

  snprintf(msg, sizeof(msg), "msg%d", rand());
  code = rand();
  snprintf(dmsg, sizeof(dmsg), "dmsg%d", rand());
  dcode = rand();

  BOOST_CHECK(foreman_error_setmessage(err, msg));
  BOOST_CHECK(foreman_error_setcode(err, code));
  BOOST_CHECK(foreman_error_setdetailmessage(err, dmsg));
  BOOST_CHECK(foreman_error_setdetailcode(err, dcode));

  BOOST_CHECK(foreman_error_getmessage(err, &rmsg));
  BOOST_CHECK(foreman_error_getcode(err, &rcode));
  BOOST_CHECK(foreman_error_getdetailmessage(err, &rdmsg));
  BOOST_CHECK(foreman_error_getdetailcode(err, &rdcode));

  BOOST_CHECK_EQUAL(msg, rmsg);
  BOOST_CHECK_EQUAL(code, rcode);
  BOOST_CHECK_EQUAL(dmsg, rdmsg);
  BOOST_CHECK_EQUAL(dcode, rdcode);

  BOOST_CHECK(foreman_error_delete(err));
}

BOOST_AUTO_TEST_SUITE_END()
