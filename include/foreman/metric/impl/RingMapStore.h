/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_RINGMAP_STORE_H_
#define _FOREMANCC_METRIC_RINGMAP_STORE_H_

#include <foreman/metric/impl/ArrayTimeSeries.h>
#include <foreman/metric/impl/TimeSeriesMapStore.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // RingMapStore
  ////////////////////////////////////////////////

  class RingMapTimeSeries : public RingArrayTimeSeries {
public:
    RingMapTimeSeries(){};
    ~RingMapTimeSeries(){};
  };

  class RingMapStore : public TimeSeriesMapStore {
public:
    RingMapStore();
    ~RingMapStore();

    bool open();
    bool isOpened();
    bool close();
    bool realloc();
  };
}
}

#endif
