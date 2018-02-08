/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/Metrics.h>
#include <foreman/metric/metric-c.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// foreman_metric_datapoints_getname
////////////////////////////////////////////////

const char* foreman_metric_metrics_getname(ForemanMetrics* m)
{
  if (!m)
    return "";
  return ((Metrics*)m)->getName();
}

////////////////////////////////////////////////
// foreman_metric_datapoints_size
////////////////////////////////////////////////

size_t foreman_metric_metrics_getdatapointsize(ForemanMetrics* m)
{
  if (!m)
    return 0;
  return ((Metrics*)m)->size();
}

////////////////////////////////////////////////
// foreman_metric_datapoints_get
////////////////////////////////////////////////

ForemanMetricDataPoint* foreman_metric_metrics_getdatapoint(ForemanMetrics* m, size_t n)
{
  if (!m)
    return NULL;
  return ((Metrics*)m)->at(n).get();
}
