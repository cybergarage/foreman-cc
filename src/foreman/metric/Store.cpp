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

bool Store::analyzeData(Query* q, ResultSet* analyzeRs)
{
  ResultSet firstMetricsRs;
  if (!queryData(q, &firstMetricsRs))
    return false;
  
  auto firstMetrics = firstMetricsRs.firstMetrics();
  
#if defined(FOREMAN_ENABLE_ALGLIB)
  alglib::real_1d_array firstMetricsData;
  if (!firstMetrics->getMetricsValues(firstMetricsData))
    return false;
#else
  return false;
#endif

  Query qAll;
  qAll.setTarget("*"); // TODO : Define "*" as a constant value
  
  ResultSet allMetricsRs;
  if (!queryMetric(&qAll, &allMetricsRs))
    return false;
  
  for (auto m = allMetricsRs.firstMetrics(); m; m = allMetricsRs.nextMetrics()) {
#if defined(FOREMAN_ENABLE_ALGLIB)
    alglib::real_1d_array metricsData;
    if (!m->getMetricsValues(metricsData))
      continue;

    auto corr = alglib::pearsoncorr2(firstMetricsData, metricsData);
    if (isnan(corr)) {
      continue;
    }
#endif

#if defined(FOREMAN_ENABLE_ALGLIB)
    auto rm = new Metrics();
    rm->setName(m->getName());
    
    // [0] : PPMCC
    auto dp = new DataPoint();
    dp->setValue(corr);
    rm->addDataPoint(dp);

    analyzeRs->addMetrics(rm);
#endif
  }

  return true;
}
