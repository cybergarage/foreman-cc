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
// foreman_datapoint_gettimestamp
////////////////////////////////////////////////

time_t foreman_datapoint_gettimestamp(ForemanDataPoint* dp)
{
  if (!dp)
    return 0;
  return ((DataPoint*)dp)->getTimestamp();
}

////////////////////////////////////////////////
// foreman_datapoint_getvalue
////////////////////////////////////////////////

double foreman_datapoint_getvalue(ForemanDataPoint* dp)
{
  if (!dp)
    return 0.0;
  return ((DataPoint*)dp)->getValue();
}
