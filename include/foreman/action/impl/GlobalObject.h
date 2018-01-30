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

#include <foreman/metric/Store.h>
#include <foreman/register/Store.h>
#include <foreman/registry/Store.h>

namespace Foreman {
namespace Action {
  void SetGlobalRegisterStore(Foreman::Register::Store* store);
  void SetGlobalRegistryStore(Foreman::Registry::Store* store);
  void SetGlobalMetricStore(Foreman::Metric::Store* store);

  Foreman::Register::Store* GetGlobalRegisterStore();
  Foreman::Registry::Store* GetGlobalRegistryStore();
  Foreman::Metric::Store* GetGlobalMetricStore();
}
}

#endif
