/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/ResultSet.h>

using namespace Foreman;

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
  currIt_ = DataPointsMap::end();
  return true;
}

////////////////////////////////////////////////
// gets
////////////////////////////////////////////////

std::shared_ptr<DataPoints> ResultSet::gets()
{
  currIt_ = dataPointsMap_.begin();
  //if (currIt_ == DataPointsMap::end())
  //  return NULL;
  return currIt_->second;
}

////////////////////////////////////////////////
// next
////////////////////////////////////////////////

std::shared_ptr<DataPoints> ResultSet::next()
{
  if (currIt_ == DataPointsMap::end())
    return NULL;

  currIt_++;
  if (!currIt_)
    return NULL;

  if (currIt_ == DataPointsMap::end())
    return NULL;
  return currIt_->second;
}
