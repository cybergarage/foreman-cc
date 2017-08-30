/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_RESULTSET_H_
#define _FOREMANCC_RESULTSET_H_

#include <foreman/Metric.h>
#include <foreman/Platform.h>

namespace Foreman {

////////////////////////////////////////////////
// ResultSet
////////////////////////////////////////////////

class ResultSet {
  public:
  ResultSet();
  virtual ~ResultSet();

  bool clear();

  size_t count;
  double* values;
};
}

#endif
