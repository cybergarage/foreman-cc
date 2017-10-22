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
#include <foreman/metric/Store.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// foreman_store_delete
////////////////////////////////////////////////

bool foreman_store_delete(ForemanStore* store)
{
  if (!store)
    return false;
  delete (Foreman::Metric::Store*)(store);
  return true;
}

////////////////////////////////////////////////
// foreman_store_setretentioninterval
////////////////////////////////////////////////

bool foreman_store_setretentioninterval(ForemanStore* store, time_t value)
{
  if (!store)
    return false;
  return ((Foreman::Metric::Store*)(store))->setRetentionInterval(value);
}

////////////////////////////////////////////////
// foreman_store_getretentioninterval
////////////////////////////////////////////////

time_t foreman_store_getretentioninterval(ForemanStore* store)
{
  if (!store)
    return 0;
  return ((Foreman::Metric::Store*)(store))->getRetentionInterval();
}

////////////////////////////////////////////////
// foreman_store_open
////////////////////////////////////////////////

bool foreman_store_open(ForemanStore* store)
{
  if (!store)
    return false;
  return ((Foreman::Metric::Store*)(store))->open();
}

////////////////////////////////////////////////
// foreman_store_close
////////////////////////////////////////////////

bool foreman_store_close(ForemanStore* store)
{
  if (!store)
    return false;
  return ((Foreman::Metric::Store*)(store))->close();
}

////////////////////////////////////////////////
// foreman_store_addmetric
////////////////////////////////////////////////

bool foreman_store_addmetric(ForemanStore* store, ForemanMetric* m)
{
  if (!store || !m)
    return false;

  if (((Foreman::Metric::Store*)(store))->addValue(*((const Foreman::Metric::Metric*)(m))))
    return true;

  std::shared_ptr<Foreman::Metric::Metric> cm = std::shared_ptr<Foreman::Metric::Metric>(new Foreman::Metric::Metric(*((const Foreman::Metric::Metric*)(m))));
  if (!((Foreman::Metric::Store*)(store))->addMetric(cm))
    return false;

  return ((Foreman::Metric::Store*)(store))->addValue(*((const Foreman::Metric::Metric*)(m)));
}

////////////////////////////////////////////////
// foreman_store_query
////////////////////////////////////////////////

bool foreman_store_query(ForemanStore* store, ForemanQuery* q, ForemanResultSet* rs)
{
  if (!store || !q || !rs)
    return false;

  if (!((Foreman::Metric::Store*)(store))->getValues(((Foreman::Metric::Query*)(q)), ((Foreman::Metric::ResultSet*)(rs))))
    return false;

  return true;
}
