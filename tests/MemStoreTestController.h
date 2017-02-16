/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_MEMSTORETESTCONTROLLER_H_
#define _FOREMANCC_MEMSTORETESTCONTROLLER_H_

#include <foreman/MemStore.h>

////////////////////////////////////////////////
// MemStoreTestContoller
////////////////////////////////////////////////

class MemStoreTestContoller {
  public:
  MemStoreTestContoller();
  virtual ~MemStoreTestContoller();

  void run(Foreman::MemStore* store);
};

#endif
