/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_MEMSTORETESTCONTROLLER_H_
#define _FOREMANCC_MEMSTORETESTCONTROLLER_H_

#include <foreman/MemStore.h>

#define FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL 60
#define FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_HOUR 6
#define FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_SEC (60 * 60 * FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_HOUR)
#define FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_COUNT (FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_PERIOD_SEC / FORMANCC_MEMSTORETESTCONTROLLER_RETENSION_INTERVAL)

#define FORMANCC_MEMSTORETESTCONTROLLER_METRICS_COUNT 500
#define FORMANCC_MEMSTORETESTCONTROLLER_METRICS_NAME_PREFIX "name"

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
