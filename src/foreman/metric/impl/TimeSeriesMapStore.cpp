/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/impl/TimeSeriesMapStore.h>
#include <regex>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// TimeSeriesMapStore
////////////////////////////////////////////////

TimeSeriesMapStore::TimeSeriesMapStore()
{
  tsMap_ = std::shared_ptr<TimeSeriesMap>(new TimeSeriesMap());
}

TimeSeriesMapStore::~TimeSeriesMapStore()
{
}

////////////////////////////////////////////////
// addData
////////////////////////////////////////////////

bool TimeSeriesMapStore::addData(const Metric& m)
{
  return tsMap_->addValue(m);
}

bool TimeSeriesMapStore::addData(const MetricArray& values)
{
  for (auto m : values) {
    if (!addData(*m))
      return false;
  }
  return true;
}

////////////////////////////////////////////////
// queryMetric
////////////////////////////////////////////////

bool TimeSeriesMapStore::queryMetric(Query* q, ResultSet* rs)
{
  if (!q || !rs)
    return false;

  std::string likeName = q->getTarget();
  std::regex nameRegex(likeName);

  for (auto m : *tsMap_) {
    auto name = m.first;
    if (!regex_match(name, nameRegex))
      continue;
    auto ms = std::shared_ptr<Metrics>(new Metrics);
    ms->setName(name);
    if (!rs->addMetrics(ms))
      return false;
  }

  return true;
}

////////////////////////////////////////////////
// queryData
////////////////////////////////////////////////

bool TimeSeriesMapStore::queryData(Query* q, ResultSet* rs)
{
  return tsMap_->getValues(q, rs);
}

size_t TimeSeriesMapStore::getColumnCount()
{
  if (retentionInterval_ == 0)
    return 0;
  return (int)(ceil(((double)retentionPeriod_ / (double)retentionInterval_)));
}

bool TimeSeriesMapStore::addMetric(std::shared_ptr<Metric> m)
{
  // TODO
  return true;
}
