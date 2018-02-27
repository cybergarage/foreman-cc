/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <math.h>

#include <foreman/Const.h>
#include <foreman/Platform.h>
#include <foreman/metric/Store.h>

#if defined(FOREMAN_ENABLE_ALGLIB)
#include <alglib/statistics.h>
#endif

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

bool Store::setRetentionInterval(time_t value)
{
  retentionInterval_ = value;
  return true;
}

////////////////////////////////////////////////
// getRetentionInterval
////////////////////////////////////////////////

time_t Store::getRetentionInterval()
{
  return retentionInterval_;
}

////////////////////////////////////////////////
// setRetentionPeriod
////////////////////////////////////////////////

bool Store::setRetentionPeriod(time_t sec)
{
  retentionPeriod_ = sec;
  return true;
};

////////////////////////////////////////////////
// getRetentionPeriod
////////////////////////////////////////////////

time_t Store::getRetentionPeriod()
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
// addValues
////////////////////////////////////////////////

bool Store::addData(const MetricArray& values)
{
  for (auto value : values) {
    if (!addData(*value))
      return false;
  }

  return true;
}

////////////////////////////////////////////////
// analyzeData
////////////////////////////////////////////////

bool Store::analyzeData(Query* q, ResultSet* rs)
{
#if defined(FOREMAN_ENABLE_ALGLIB)
  v = pearsoncorr2(x, y);
#endif

  return false;
}
