/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <algorithm>
#include <cmath>

#include <foreman/Const.h>
#include <foreman/Platform.h>
#include <foreman/metric/Store.h>

#if defined(FOREMAN_ENABLE_ALGLIB)
#if defined(HAVE_LIBALGLIB_STATISTICS_H)
#include <libalglib/statistics.h>
#else
#include <alglib/statistics.h>
#endif
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
  if (!firstMetrics)
    return false;

  MetricsArray resultMs;

#if defined(FOREMAN_ENABLE_ALGLIB)
  alglib::real_1d_array firstMetricsData;
  if (!firstMetrics->getMetricsValues(firstMetricsData))
    return false;
#endif

  Query qAll;
  qAll.setTarget("*"); // TODO : Define "*" as a constant value

  ResultSet allMetricsRs;
  if (!queryMetric(&qAll, &allMetricsRs))
    return false;

  Query qm = *q;
  for (auto m = allMetricsRs.firstMetrics(); m; m = allMetricsRs.nextMetrics()) {
    qm.setTarget(m->getName());
    ResultSet metricRs;
    if (!queryData(&qm, &metricRs))
      return false;

    auto otherFirstMetrics = metricRs.firstMetrics();
    if (!otherFirstMetrics)
      continue;

#if defined(FOREMAN_ENABLE_ALGLIB)
    alglib::real_1d_array otherMetricsData;
    if (!otherFirstMetrics->getMetricsValues(otherMetricsData))
      continue;

    double corr;
    try {
      corr = alglib::pearsoncorr2(firstMetricsData, otherMetricsData);
      if (std::isnan(corr)) {
        continue;
      }
    }
    catch (...) {
      return false;
    }
#endif

    auto rm = new Metrics();
    rm->setName(m->getName());

    // [0] : PPMCC
    auto dp = new DataPoint();
#if defined(FOREMAN_ENABLE_ALGLIB)
    dp->setValue(corr);
#else
    dp->setValue(NAN);
#endif
    rm->addDataPoint(dp);

    // [1] : Max Value
    auto maxIndex = otherFirstMetrics->getMaxValueIndex();
    if (0 < maxIndex) {
      auto maxDp = otherFirstMetrics->getDataPoint(maxIndex);
      auto dp = new DataPoint();
      if (dp) {
        dp->setValue(maxDp->getValue());
        dp->setTimestamp(maxDp->getTimestamp());
        rm->addDataPoint(dp);
      }
    }

    resultMs.addMetrics(rm);
  }

  // Sort result

  std::sort(
      resultMs.begin(),
      resultMs.end(),
      [](const std::shared_ptr<Metrics> m1, const std::shared_ptr<Metrics> m2) {
        auto m1dp = m1->getDataPoint(0);
        auto m2dp = m2->getDataPoint(0);
        return m1dp->getValue() > m2dp->getValue();
      });

  for (auto rm : resultMs) {
    analyzeRs->addMetrics(rm);
  }

  return true;
}
