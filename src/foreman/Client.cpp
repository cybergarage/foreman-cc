/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string.h>

#include <foreman/Client.h>
#include <foreman/Const.h>
#include <foreman/net/HttpClient.h>

using namespace Foreman;

////////////////////////////////////////////////
//  Client
////////////////////////////////////////////////

Client::Client()
{
  setHost(FOREMANCC_DEFAULT_SERVER_HOST);
  setPort(FOREMANCC_DEFAULT_RPC_PORT);
}

Client::~Client()
{
}

////////////////////////////////////////////////
// setHost
////////////////////////////////////////////////

void Client::setHost(const std::string& value)
{
  this->host = value;
}

////////////////////////////////////////////////
// setPort
////////////////////////////////////////////////

void Client::setPort(int port)
{
  this->port = port;
}

////////////////////////////////////////////////
// query
////////////////////////////////////////////////

bool Client::query(const std::string& query, std::string* res)
{
  char urlPath[256];
  if (snprintf(urlPath, sizeof(urlPath), "http://%s:%d%s?%s=%s", this->host.c_str(), this->port, FOREMANCC_HTTP_REQUEST_FQL_PATH, FOREMANCC_HTTP_REQUEST_FQL_QUERY_PARAM, query.c_str())) {
    return false;
  }

  HttpClient client;
  if (client.get(urlPath, *res))
    return false;

  return true;
}

////////////////////////////////////////////////
// ping
////////////////////////////////////////////////

bool Client::ping()
{
  std::string jsonRes;
  if (!query("EXPORT FROM CONFIG", &jsonRes))
    return false;
  return true;
}
