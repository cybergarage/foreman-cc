/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <math.h>

#include <foreman/Const.h>
#include <foreman/Store.h>

using namespace Foreman;

////////////////////////////////////////////////
// Store
////////////////////////////////////////////////

Store::Store()
{
  setRetentionInterval(FOREMANCC_STORE_DEFAULT_RETENTIONI_INTERVAL);
}

Store::~Store()
{
}

////////////////////////////////////////////////
// Store
////////////////////////////////////////////////

bool Store::setRetentionInterval(time_t value)
{
  retentionInterval_ = value;
  return true;
}

////////////////////////////////////////////////
// Store
////////////////////////////////////////////////

time_t Store::getRetentionInterval()
{
  return retentionInterval_;
}

////////////////////////////////////////////////
// addMetric
////////////////////////////////////////////////

bool Store::addMetric(std::shared_ptr<Foreman::Metric> m)
{
  return metricMap_.addMetric(m);
}

////////////////////////////////////////////////
// findMetric
////////////////////////////////////////////////

std::shared_ptr<Metric> Store::findMetric(const std::string& name)
{
  return metricMap_.findMetric(name);
}

////////////////////////////////////////////////
// findMetric
////////////////////////////////////////////////

std::shared_ptr<std::vector<std::shared_ptr<Metric>>> Store::getMetrics()
{
  return metricMap_.getMetrics();
}

////////////////////////////////////////////////
// addValues
////////////////////////////////////////////////

bool Store::addValues(const Metrics& values)
{
  for (std::shared_ptr<Foreman::Metric> value : values) {
    if (!addValue(*value))
      return false;
  }

  return true;
}
