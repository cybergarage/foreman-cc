/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/Store.h>
#include <foreman/metric/metric-c.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// foreman_metric_store_delete
////////////////////////////////////////////////

bool foreman_metric_store_delete(ForemanMetricStore* store)
{
  if (!store)
    return false;
  delete (Foreman::Metric::Store*)(store);
  return true;
}

////////////////////////////////////////////////
// foreman_metric_store_setretentioninterval
////////////////////////////////////////////////

bool foreman_metric_store_setretentioninterval(ForemanMetricStore* store, time_t value)
{
  if (!store)
    return false;
  return ((Foreman::Metric::Store*)(store))->setRetentionInterval(value);
}

////////////////////////////////////////////////
// foreman_metric_store_getretentioninterval
////////////////////////////////////////////////

time_t foreman_metric_store_getretentioninterval(ForemanMetricStore* store)
{
  if (!store)
    return 0;
  return ((Foreman::Metric::Store*)(store))->getRetentionInterval();
}

////////////////////////////////////////////////
// foreman_metric_store_open
////////////////////////////////////////////////

bool foreman_metric_store_open(ForemanMetricStore* store)
{
  if (!store)
    return false;
  return ((Foreman::Metric::Store*)(store))->open();
}

////////////////////////////////////////////////
// foreman_metric_store_close
////////////////////////////////////////////////

bool foreman_metric_store_close(ForemanMetricStore* store)
{
  if (!store)
    return false;
  return ((Foreman::Metric::Store*)(store))->close();
}

////////////////////////////////////////////////
// foreman_metric_store_clear
////////////////////////////////////////////////

bool foreman_metric_store_clear(ForemanMetricStore* store)
{
  if (!store)
    return false;

  return ((Foreman::Metric::Store*)(store))->clear();
}

////////////////////////////////////////////////
// foreman_metric_store_addmetric
////////////////////////////////////////////////

bool foreman_metric_store_addmetric(ForemanMetricStore* store, ForemanMetric* m)
{
  if (!store || !m)
    return false;

  if (((Foreman::Metric::Store*)(store))->addData(*((const Foreman::Metric::Metric*)(m))))
    return true;

  auto cm = std::shared_ptr<Foreman::Metric::Metric>(new Foreman::Metric::Metric(*((const Foreman::Metric::Metric*)(m))));
  if (!((Foreman::Metric::Store*)(store))->addMetric(cm))
    return false;

  return ((Foreman::Metric::Store*)(store))->addData(*((const Foreman::Metric::Metric*)(m)));
}

////////////////////////////////////////////////
// foreman_metric_store_querymetric
////////////////////////////////////////////////

bool foreman_metric_store_querymetric(ForemanMetricStore* store, ForemanMetricQuery* q, ForemanMetricResultSet* rs)
{
  if (!store || !q || !rs)
    return false;

  if (!((Foreman::Metric::Store*)(store))->queryMetric(((Foreman::Metric::Query*)(q)), ((Foreman::Metric::ResultSet*)(rs))))
    return false;

  return true;
}

////////////////////////////////////////////////
// foreman_metric_store_querydata
////////////////////////////////////////////////

bool foreman_metric_store_querydata(ForemanMetricStore* store, ForemanMetricQuery* q, ForemanMetricResultSet* rs)
{
  if (!store || !q || !rs)
    return false;

  if (!((Foreman::Metric::Store*)(store))->queryData(((Foreman::Metric::Query*)(q)), ((Foreman::Metric::ResultSet*)(rs))))
    return false;

  return true;
}

////////////////////////////////////////////////
// foreman_metric_store_analyzedata
////////////////////////////////////////////////

bool foreman_metric_store_analyzedata(ForemanMetricStore* store, ForemanMetricQuery* q, ForemanMetricResultSet* rs, ForemanError* err)
{
  if (!store || !q || !rs)
    return false;

  if (!((Foreman::Metric::Store*)(store))->analyzeData(((Foreman::Metric::Query*)(q)), ((Foreman::Metric::ResultSet*)(rs)), ((Foreman::Error*)(err))))
    return false;

  return true;
}

size_t foreman_metric_store_query_delete_expired_metrics(ForemanMetricStore* store)
{
  if (!store)
    return 0;
  return ((Foreman::Metric::Store*)(store))->deleteExpiredMetrics();
}
