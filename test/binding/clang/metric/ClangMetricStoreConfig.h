/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_CLANG_METRIC_STORE_CONFIG_H_
#define _FOREMANCC_CLANG_METRIC_STORE_CONFIG_H_

#include "../../../metric/StoreTestConfig.h"

class ClangMetricsStoreTestConfig : public Foreman::Metric::DefaultStoreTestConfig {
  public:
  ClangMetricsStoreTestConfig() {}
};

#endif
