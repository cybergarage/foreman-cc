/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string.h>

#include <foreman/net/Graphite.h>
#include <foreman/net/HttpClient.h>
#include <foreman/net/Socket.h>

using namespace Foreman;

////////////////////////////////////////////////
//  Graphite
////////////////////////////////////////////////

Graphite::Graphite()
{
}

Graphite::~Graphite()
{
}

////////////////////////////////////////////////
// setHost
////////////////////////////////////////////////

void Graphite::setHost(const std::string& value)
{
  host = value;
}

////////////////////////////////////////////////
// setCarbonPort
////////////////////////////////////////////////

void Graphite::setCarbonPort(int port)
{
  carbonPort = port;
}

////////////////////////////////////////////////
// setHttpPort
////////////////////////////////////////////////

void Graphite::setHttpPort(int port)
{
  httpPort = port;
}

////////////////////////////////////////////////
// addValue
////////////////////////////////////////////////

bool Graphite::addValue(const std::string& path, time_t ts, double value)
{
  char pickleMsg[128];

  if (snprintf(pickleMsg, sizeof(pickleMsg), "%s %ld %lf", path.c_str(), ts, value) < 0)
    return false;

  Socket sock;

  if (!sock.connect(host, carbonPort))
    return false;

  if (sock.send(pickleMsg, strlen(pickleMsg)) <= 0)
    return false;

  sock.close();

  return true;
}

////////////////////////////////////////////////
// getValues
////////////////////////////////////////////////

bool Graphite::getValues(const std::string& path, time_t beginTs, time_t endTs, time_t interval, double** values, size_t* valueCnt)
{
  struct tm* tm;

  // Graphite : ABSOLUTE_TIME is in the format HH:MM_YYMMDD, YYYYMMDD, MM/DD/YY

  char sinceStr[32];
  tm = localtime(&beginTs);
  if (strftime(sinceStr, sizeof(sinceStr), "%H:%M_%Y%m%d", tm) == 0)
    return false;

  char endStr[32];
  tm = localtime(&endTs);
  if (strftime(endStr, sizeof(endStr), "%H:%M_%Y%m%d", tm) == 0)
    return false;

  char urlPath[256];
  if (snprintf(urlPath, sizeof(urlPath), "http://%s/render?target=%s&from=%s&until=%s&format=csv", host.c_str(), path.c_str(), sinceStr, endStr) < 0)
    return false;

  HttpClient cli;
  std::string content;
  if (cli.get(urlPath, content))
    return false;

  return true;
}
