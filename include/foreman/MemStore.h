/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_MEMSTORE_H_
#define _FOREMANCC_MEMSTORE_H_

#include <foreman/Platform.h>

namespace Foreman {

class MemStore {

public:
  MemStore();
  virtual ~MemStore();
  
  virtual bool open() = 0;
  virtual bool isOpened() = 0;
  virtual bool close() = 0;
};

}

#endif
