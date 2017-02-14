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

#include <foreman/MemStore.h>

using namespace Foreman;

class NullMemStore : public MemStore {
public:
  NullMemStore() {}
  ~NullMemStore() {}
  
  bool open() {return true;}
  bool isOpened() {return true;}
  bool close() {return true;}
};

BOOST_AUTO_TEST_CASE(NewMemStore)
{
  MemStore *store = new NullMemStore();
  delete store;
}
