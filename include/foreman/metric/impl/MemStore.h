/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_MEMSTORE_H_
#define _FOREMANCC_METRIC_MEMSTORE_H_

#include <foreman/metric/Store.h>
#include <time.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // MemStore
  ////////////////////////////////////////////////

  class MemStore : public Store {
public:
    MemStore();
    virtual ~MemStore();

    virtual bool clear()
    {
      return true;
    }

    virtual bool realloc()
    {
      return true;
    }

    virtual size_t getMemoryUsage()
    {
      return 0;
    }

    size_t getStorageUsage()
    {
      return 0;
    }

    size_t getColumnCount();
    size_t getRowCount();
  };
}
}

#endif
