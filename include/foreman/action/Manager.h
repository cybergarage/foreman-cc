/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_SCRIPT_H_
#define _FOREMANCC_ACTION_SCRIPT_H_

#include <map>
#include <string>

#include <foreman/Platform.h>
#include <foreman/action/Parameter.h>
#include <foreman/common/Error.h>
#include <foreman/util/Mutex.h>

#include <foreman/metric/Store.h>
#include <foreman/register/Store.h>
#include <foreman/registry/Store.h>

#include <foreman/action/Engine.h>
#include <foreman/action/Method.h>

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // ScriptManager
  ////////////////////////////////////////////////

  class ScriptManager {

public:
    ScriptManager();
    virtual ~ScriptManager();

    bool setRegisterStore(Foreman::Register::Store* store);
    bool setRegistryStore(Foreman::Registry::Store* store);
    bool setMetricStore(Foreman::Metric::Store* store);

    Foreman::Register::Store* getRegisterStore();
    Foreman::Registry::Store* getRegistryStore();
    Foreman::Metric::Store* getMetricStore();

    bool addMethod(Method* method, Error* error);

    bool hasMethod(const std::string& name) const
    {
      return this->methodMap.hasMethod(name);
    }

    bool removeMethod(const std::string& method, Error* error);
    bool removeAllMethods(Error* error);

    bool addEngine(ScriptEngine* engine);

    bool hasEngine(const std::string& lang) const
    {
      return this->engineMap.hasEngine(lang);
    }

    bool execMethod(const std::string& name, const Parameters* params, Parameters* results, Error* error);

private:
    bool addMethod(const std::string& method, const std::string& lang, const std::string& script, Error* error);

private:
    MethodMap methodMap;
    ScriptEngineMap engineMap;

public:
    const MethodMap* getMethodMap()
    {
      return &methodMap;
    }

    const ScriptEngineMap* getEngineMap()
    {
      return &engineMap;
    }
  };

  ////////////////////////////////////////////////
  // Manager
  ////////////////////////////////////////////////

  class Manager : public ScriptManager {

public:
    Manager();
    virtual ~Manager();
  };
}
}

#endif
