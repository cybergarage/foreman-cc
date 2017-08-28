/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_QUERY_H_
#define _FOREMANCC_QUERY_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <time.h>

#include <foreman/Platform.h>

namespace Foreman {

////////////////////////////////////////////////
// Query
////////////////////////////////////////////////

class Query {
  public:
  Query();
  virtual ~Query();

  std::string target;
  time_t from;
  time_t until;
  time_t interval;
};

}

#endif
