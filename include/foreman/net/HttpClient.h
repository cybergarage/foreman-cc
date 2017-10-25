/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMAN_NET_HTTPCLIENT_H_
#define _FOREMAN_NET_HTTPCLIENT_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>

namespace Foreman {

class HttpClient {

  public:
  HttpClient();
  ~HttpClient();

  bool get(const std::string& uri, std::string& content);
};
}

#endif
