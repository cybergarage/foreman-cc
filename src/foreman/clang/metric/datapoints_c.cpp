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
// foreman_metric_datapoints_getname
////////////////////////////////////////////////

const char* foreman_metric_datapoints_getname(ForemanMetricDataPoints* dps)
{
  if (!dps)
    return "";
  return ((DataPoints*)dps)->getName();
}

////////////////////////////////////////////////
// foreman_metric_datapoints_size
////////////////////////////////////////////////

size_t foreman_metric_datapoints_size(ForemanMetricDataPoints* dps)
{
  if (!dps)
    return 0;
  return ((DataPoints*)dps)->size();
}

////////////////////////////////////////////////
// foreman_metric_datapoints_get
////////////////////////////////////////////////

ForemanMetricDataPoint* foreman_metric_datapoints_get(ForemanMetricDataPoints* dps, size_t n)
{
  if (!dps)
    return NULL;
  return ((DataPoints*)dps)->at(n).get();
}
