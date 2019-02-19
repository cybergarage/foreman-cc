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

#include <foreman/util/Mutex.h>

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // ScriptManager
  ////////////////////////////////////////////////

  class ScriptManager : public Mutex {

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
      return this->methodMap->hasMethod(name);
    }

    Method* getMethod(const std::string& name)
    {
      return this->methodMap->getMethod(name);
    }

    bool removeMethod(const std::string& method, Error* error);
    bool removeAllMethods(Error* error);

    bool addEngine(ScriptEngine* engine);

    bool hasEngine(const std::string& lang) const
    {
      return this->engineMap->hasEngine(lang);
    }

    bool execMethod(const std::string& name, const Parameters* params, Parameters* results, Error* error);

    const MethodMap* getMethodMap()
    {
      return this->methodMap;
    }

    const ScriptEngineMap* getEngineMap()
    {
      return this->engineMap;
    }

private:
    MethodMap *methodMap;
    ScriptEngineMap *engineMap;
  };

  ////////////////////////////////////////////////
  // Manager
  ////////////////////////////////////////////////

  class Manager : public ScriptManager {

public:
    Manager();
    virtual ~Manager();
  };

  ////////////////////////////////////////////////
  // DefaultManager
  ////////////////////////////////////////////////

  class DefaultManager : public Manager {

public:
    DefaultManager();
    virtual ~DefaultManager();
  };
}
}

#endif
