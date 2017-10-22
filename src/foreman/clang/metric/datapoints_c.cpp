/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/foreman-c.h>
#include <foreman/metric/DataPoint.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// foreman_datapoints_getname
////////////////////////////////////////////////

const char* foreman_datapoints_getname(ForemanDataPoints* dps)
{
  if (!dps)
    return "";
  return ((DataPoints*)dps)->getName();
}

////////////////////////////////////////////////
// foreman_datapoints_size
////////////////////////////////////////////////

size_t foreman_datapoints_size(ForemanDataPoints* dps)
{
  if (!dps)
    return 0;
  return ((DataPoints*)dps)->size();
}

////////////////////////////////////////////////
// foreman_datapoints_get
////////////////////////////////////////////////

ForemanDataPoint* foreman_datapoints_get(ForemanDataPoints* dps, size_t n)
{
  if (!dps)
    return NULL;
  return ((DataPoints*)dps)->at(n).get();
}
