/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_ENGINE_H_
#define _FOREMANCC_ACTION_ENGINE_H_

#include <map>
#include <string>

#include <foreman/Platform.h>
#include <foreman/action/Method.h>
#include <foreman/action/Parameter.h>
#include <foreman/common/Error.h>
#include <foreman/util/Mutex.h>

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // ScriptEngine
  ////////////////////////////////////////////////

  class ScriptEngine {

public:
    ScriptEngine(const std::string& lang);
    virtual ~ScriptEngine();

    const std::string& getLanguage() const
    {
      return this->language;
    }

    virtual bool compile(Method* method, Error* error) = 0;
    virtual bool run(Method* method, const Parameters* params, Parameters* results, Error* error) = 0;

    void lock() const
    {
      mutex.lock();
    }

    void unlock() const
    {
      mutex.unlock();
    }

private:
    void init();

private:
    std::string language;
    mutable Mutex mutex;
  };

  ////////////////////////////////////////////////
  // ScriptEngineMap
  ////////////////////////////////////////////////

  class ScriptEngineMap : public std::map<std::string, ScriptEngine*> {

public:
    ScriptEngineMap();
    virtual ~ScriptEngineMap();

    bool hasEngine(const std::string& lang) const;
    ScriptEngine* getEngine(const std::string& lang);

    void clear();

private:
    void init();
  };
}
}

#endif
