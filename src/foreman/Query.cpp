/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <math.h>

#include <foreman/Query.h>

using namespace Foreman;

////////////////////////////////////////////////
// Query
////////////////////////////////////////////////

Query::Query()
{
  from = 0;
  until = 0;
  interval = 0;
}

Query::~Query()
{
}

////////////////////////////////////////////////
// getDataPointCount
////////////////////////////////////////////////

bool Query::getDataPointCount(size_t* count)
{
  if (until <= from)
    return false;

  *count = ((until - from) / interval);
  if (*count <= 0)
    return false;

  return true;
}
