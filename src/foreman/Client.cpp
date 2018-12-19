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

using namespace Foreman;

////////////////////////////////////////////////
//  Client
////////////////////////////////////////////////

Client::Client()
{
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
