/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_METRIC_GRAPHITE_STORE_H_
#define _FOREMANCC_METRIC_GRAPHITE_STORE_H_

#include <foreman/metric/impl/MemStore.h>

namespace Foreman {
namespace Metric {

////////////////////////////////////////////////
// GraphiteStore
////////////////////////////////////////////////

#if defined(FOREMAN_ENABLE_GRAPHITE)

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

#endif
}
}

#endif
