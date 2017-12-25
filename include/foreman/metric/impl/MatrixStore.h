/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_MATRIX_STORE_H_
#define _FOREMANCC_METRIC_MATRIX_STORE_H_

#include <time.h>

#include <sqlite3.h>

#include <foreman/metric/impl/ArrayTimeSeries.h>
#include <foreman/metric/impl/TimeSeriesMapStore.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // MatrixStore
  ////////////////////////////////////////////////

  class MatrixTimeSeries : public StaticArrayTimeSeries {
public:
    MatrixTimeSeries(){};
    ~MatrixTimeSeries(){};
  };

  class MatrixStore : public TimeSeriesMapStore {
public:
    MatrixStore();
    ~MatrixStore();

    bool open();
    bool isOpened();
    bool close();

    bool realloc();
  };
}
}

#endif
