/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMAN_NET_GRAPHITE_H_
#define _FOREMAN_NET_GRAPHITE_H_

#include <memory>
#include <string>
#include <time.h>

namespace Foreman {

class Graphite {

  public:
  Graphite();
  ~Graphite();

  void setHost(const std::string& host);
  void setCarbonPort(int port);
  void setHttpPort(int port);

  bool addValue(const std::string& path, time_t ts, double value);
  bool getValues(const std::string& path, time_t beginTs, time_t endTs, time_t interval, std::shared_ptr<double>& values, size_t& valueCnt);

  private:
  std::string host;
  int carbonPort;
  int httpPort;
};
}

#endif
