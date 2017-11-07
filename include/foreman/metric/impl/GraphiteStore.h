/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_GRAPHITE_STORE_H_
#define _FOREMANCC_METRIC_GRAPHITE_STORE_H_

#if defined(FOREMAN_ENABLE_GRAPHITE)

#include <foreman/metric/impl/MemStore.h>
#include <foreman/net/Graphite.h>

namespace Foreman {
namespace Metric {

  ////////////////////////////////////////////////
  // GraphiteStore
  ////////////////////////////////////////////////

  class GraphiteStore : public MemStore {
public:
    GraphiteStore();
    ~GraphiteStore();

    bool open();
    bool isOpened();
    bool close();

    void setHost(const std::string& host);
    void setCarbonPort(int port);
    void setHttpPort(int port);

    bool addValue(const Metric& m);
    bool getValues(Query* q, ResultSet* rs);

private:
    Graphite graphite;
  };
}
}

#endif

#endif
