/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/DataPoint.h>
#include <foreman/metric/metric-c.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// foreman_metric_datapoint_gettimestamp
////////////////////////////////////////////////

time_t foreman_metric_datapoint_gettimestamp(ForemanMetricDataPoint* dp)
{
  if (!dp)
    return 0;
  return ((DataPoint*)dp)->getTimestamp();
}

////////////////////////////////////////////////
// foreman_metric_datapoint_getvalue
////////////////////////////////////////////////

double foreman_metric_datapoint_getvalue(ForemanMetricDataPoint* dp)
{
  if (!dp)
    return 0.0;
  return ((DataPoint*)dp)->getValue();
}
