/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_GLOBALOBJECT_H_
#define _FOREMANCC_ACTION_GLOBALOBJECT_H_

#include <foreman/register/Store.h>

namespace Foreman {
namespace Action {
  void SetGlobalRegisterStore(Foreman::Register::Store* store);
  Foreman::Register::Store* GetGlobalRegisterStore();
}
}

#endif
