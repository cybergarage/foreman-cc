/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_BERINGEI_STORE_H_
#define _FOREMANCC_METRIC_BERINGEI_STORE_H_

#include <time.h>

#include <foreman/metric/Store.h>
#include <foreman/metric/impl/TimeSeries.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // TSmapStore
  ////////////////////////////////////////////////

  class TSmapStore : public TimeSeriesMapStore {
public:
    TSmapStore();
    ~TSmapStore();

    bool open();
    bool isOpened();
    bool close();
  };
}
}

#endif
