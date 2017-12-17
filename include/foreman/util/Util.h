/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_UTIL_H_
#define _FOREMANCC_UTIL_H_

#include <cmath>
#include <cstdlib>

namespace Foreman {

double* CreateNanDataPointValueArray(std::size_t size);

inline bool IsValidDataPointValue(double value)
{
  // NaN never compares equal with another NaN.
  return !std::isnan(value);
}
}

#endif
