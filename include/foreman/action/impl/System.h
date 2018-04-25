/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_SYSTEM_H_
#define _FOREMANCC_ACTION_SYSTEM_H_

#include <foreman/Platform.h>

#include <foreman/action/Engine.h>
#include <string>

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // SystemMethod
  ////////////////////////////////////////////////
  
  class SystemMethod : public Method {
  public:
    SystemMethod();
    ~SystemMethod();
  };
  
  ////////////////////////////////////////////////
  // SystemEngine
  ////////////////////////////////////////////////

  class SystemEngine : public ScriptEngine {

public:
    static const std::string LANGUAGE;

public:
    SystemEngine();
    ~SystemEngine();

    bool compile(Method* method, Error* error);
    bool run(Method* method, const Parameters* params, Parameters* results, Error* error);
  };
}
}

#endif
