/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_REGISTRY_STORETESTCONTROLLER_H_
#define _FOREMANCC_REGISTRY_STORETESTCONTROLLER_H_

#include <foreman/registry/Store.h>

////////////////////////////////////////////////
// StoreTestContoller
////////////////////////////////////////////////

namespace Foreman {
namespace Registry {

  class StoreTestContoller {
public:
    StoreTestContoller();
    virtual ~StoreTestContoller();

    void run(Store* store);
  };
}
}

#endif
