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
  dataPointsMap_.clear();
  currIt_ = dataPointsMap_.end();

  return true;
}

////////////////////////////////////////////////
// gets
////////////////////////////////////////////////

Metrics* ResultSet::firstDataPoint()
{
  currIt_ = dataPointsMap_.begin();

  if (currIt_ == dataPointsMap_.end())
    return NULL;

  return currIt_->second.get();
}

////////////////////////////////////////////////
// next
////////////////////////////////////////////////

Metrics* ResultSet::nextDataPoint()
{
  if (currIt_ == dataPointsMap_.end())
    return NULL;

  currIt_++;
  if (currIt_ == dataPointsMap_.end())
    return NULL;

  return currIt_->second.get();
}
