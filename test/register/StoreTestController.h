/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTER_STORETESTCONTROLLER_H_
#define _FOREMANCC_REGISTER_STORETESTCONTROLLER_H_

#include <foreman/register/Store.h>

////////////////////////////////////////////////
// StoreTestContoller
////////////////////////////////////////////////

namespace Foreman {
namespace Register {

  class StoreTestContoller {
public:
    StoreTestContoller();
    virtual ~StoreTestContoller();

    void run(Store* store);

private:
    void testInsert(Store* store);
    void testRepeatInsert(Store* store);
  };
}
}

#endif
