/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
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
#include <foreman/util/Mutex.h>

namespace Foreman {

class HttpClient : public Mutex {
  static size_t curl_response_reader(void* ptr, size_t size, size_t nmemb, std::string* s);

  public:
  HttpClient();
  ~HttpClient();

  bool encode(const std::string& str, std::string& encordedStr);
  bool get(const std::string& uri, std::string& content);

  private:
  static ssize_t InstanceCount;

};
}

#endif
