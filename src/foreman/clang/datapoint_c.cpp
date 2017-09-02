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
// foreman_datapoint_gettimestamp
////////////////////////////////////////////////

time_t foreman_datapoint_gettimestamp(ForemanDataPoint* dp)
{
  if (!dp)
    return 0;
  return ((DataPoint*)dp)->timestamp;
}

////////////////////////////////////////////////
// foreman_datapoint_getvalue
////////////////////////////////////////////////

float foreman_datapoint_getvalue(ForemanDataPoint* dp)
{
  if (!dp)
    return 0.0;
  return ((DataPoint*)dp)->timestamp;
}
