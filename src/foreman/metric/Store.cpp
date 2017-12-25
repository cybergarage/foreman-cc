/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <ctime>

#include <foreman/Const.h>
#include <foreman/metric/Store.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// Store
////////////////////////////////////////////////

Store::Store()
{
  setRetentionInterval(FOREMANCC_METRIC_STORE_DEFAULT_RETENTIONI_INTERVAL);
}

Store::~Store()
{
}

////////////////////////////////////////////////
// setRetentionInterval
////////////////////////////////////////////////

bool Store::setRetentionInterval(std::time_t value)
{
  retentionInterval_ = value;
  return true;
}

////////////////////////////////////////////////
// getRetentionInterval
////////////////////////////////////////////////

std::time_t Store::getRetentionInterval()
{
  return retentionInterval_;
}

////////////////////////////////////////////////
// setRetentionPeriod
////////////////////////////////////////////////

bool Store::setRetentionPeriod(std::time_t sec)
{
  retentionPeriod_ = sec;
  return true;
};

////////////////////////////////////////////////
// getRetentionPeriod
////////////////////////////////////////////////

std::time_t Store::getRetentionPeriod()
{
  return retentionPeriod_;
};

////////////////////////////////////////////////
// addMetric
////////////////////////////////////////////////

bool Store::addMetric(std::shared_ptr<Foreman::Metric::Metric> m)
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
  for (std::shared_ptr<Foreman::Metric::Metric> value : values) {
    if (!addValue(*value))
      return false;
  }

  return true;
}
