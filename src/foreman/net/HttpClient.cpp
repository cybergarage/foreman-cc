/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/net/HttpClient.h>
#include <uhttp/HTTP.h>

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

bool HttpClient::get(const std::string &uri, std::string &content)
{
  uHTTP::HTTPRequest httpReq;
  httpReq.setMethod(uHTTP::HTTP::GET);
  httpReq.setURL(uri);
  
  uHTTP::HTTPResponse *httpRes = httpReq.post();
  if (!httpRes->isSuccessful())
    return false;

  content = httpRes->getContent();
  
  return false;
}
