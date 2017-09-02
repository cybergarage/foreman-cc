/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/DataPoint.h>
#include <foreman/foreman-c.h>

using namespace Foreman;

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
