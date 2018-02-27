/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/metric/ResultSet.h>

using namespace Foreman::Metric;

////////////////////////////////////////////////
// ResultSet
////////////////////////////////////////////////

ResultSet::ResultSet()
{
}

ResultSet::~ResultSet()
{
  clear();
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool ResultSet::clear()
{
  metricsMap_.clear();
  currIt_ = metricsMap_.end();

  return true;
}

////////////////////////////////////////////////
// gets
////////////////////////////////////////////////

Metrics* ResultSet::firstMetrics()
{
  currIt_ = metricsMap_.begin();

  if (currIt_ == metricsMap_.end())
    return NULL;

  return currIt_->second.get();
}

////////////////////////////////////////////////
// next
////////////////////////////////////////////////

Metrics* ResultSet::nextMetrics()
{
  if (currIt_ == metricsMap_.end())
    return NULL;

  currIt_++;
  if (currIt_ == metricsMap_.end())
    return NULL;

  return currIt_->second.get();
}
