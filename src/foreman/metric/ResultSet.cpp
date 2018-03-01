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
  msArray_.clear();
  currIt_ = msArray_.end();

  return true;
}

////////////////////////////////////////////////
// gets
////////////////////////////////////////////////

Metrics* ResultSet::firstMetrics()
{
  currIt_ = msArray_.begin();

  if (currIt_ == msArray_.end())
    return NULL;

  return (*currIt_).get();
}

////////////////////////////////////////////////
// next
////////////////////////////////////////////////

Metrics* ResultSet::nextMetrics()
{
  if (currIt_ == msArray_.end())
    return NULL;

  currIt_++;
  if (currIt_ == msArray_.end())
    return NULL;

  return (*currIt_).get();
}
