/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/net/HttpClient.h>

#if defined(FOREMAN_ENABLE_UHTTPCC)
#include <uhttp/HTTP.h>
#endif

using namespace Foreman;

////////////////////////////////////////////////
//  HttpClient
////////////////////////////////////////////////

HttpClient::HttpClient()
{
}

HttpClient::~HttpClient()
{
}

////////////////////////////////////////////////
//  HttpClient
////////////////////////////////////////////////

bool HttpClient::get(const std::string& uri, std::string& content)
{
#if defined(FOREMAN_ENABLE_UHTTPCC)
  uHTTP::HTTPRequest httpReq;
  httpReq.setMethod(uHTTP::HTTP::GET);
  httpReq.setURL(uri);

  uHTTP::HTTPResponse* httpRes = httpReq.post();
  if (!httpRes->isSuccessful())
    return false;

  content = httpRes->getContent();
#endif

  return false;
}
