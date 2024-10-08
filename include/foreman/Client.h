/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMAN_CLIENT_H_
#define _FOREMAN_CLIENT_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>

namespace Foreman {

class Client {

  public:
  Client();
  ~Client();

  void setHost(const std::string& host);
  void setPort(int port);

  bool ping();
  bool query(const std::string& query, std::string* res);

  private:
  std::string host;
  int port;
};

}

#endif
