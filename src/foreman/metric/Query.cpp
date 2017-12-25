/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/Query.h>

using namespace Foreman::Metric;

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
