/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/Manager.h>
#include <foreman/action/impl/GlobalObject.h>
#include <foreman/common/Errors.h>

using namespace Foreman::Action;

////////////////////////////////////////////////
// ScriptManager
////////////////////////////////////////////////

ScriptManager::ScriptManager()
{
}

ScriptManager::~ScriptManager()
{
}

////////////////////////////////////////////////
// ?etRegisterStore
////////////////////////////////////////////////

bool ScriptManager::setRegisterStore(Foreman::Register::Store* store)
{
  SetGlobalRegisterStore(store);
  return true;
}

Foreman::Register::Store* getRegisterStore()
{
  return GetGlobalRegisterStore();
}

////////////////////////////////////////////////
// ?etRegistryStore
////////////////////////////////////////////////

bool ScriptManager::setRegistryStore(Foreman::Registry::Store* store)
{
  SetGlobalRegistryStore(store);
  return true;
}

Foreman::Registry::Store* getRegistryStore()
{
  return GetGlobalRegistryStore();
}

////////////////////////////////////////////////
// ?etMetricStore
////////////////////////////////////////////////

bool ScriptManager::setMetricStore(Foreman::Metric::Store* store)
{
  SetGlobalMetricStore(store);
  return true;
}

Foreman::Metric::Store* getMetricStore()
{
  return GetGlobalMetricStore();
}

////////////////////////////////////////////////
// setScript
////////////////////////////////////////////////

bool ScriptManager::addMethod(Method* method, Error* err)
{
  if (!method) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  std::string name = method->getName();
  if (name.length() <= 0) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  auto codeLen = method->getCodeLength();
  if (codeLen <= 0) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  std::string lang = method->getLanguage();
  if (!hasEngine(lang)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  ScriptEngine* scriptEngine = this->engineMap.getEngine(lang);
  if (!scriptEngine) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  if (!scriptEngine->compile(method, err)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  this->methodMap[name] = std::unique_ptr<Method>(method);

  return true;
}

////////////////////////////////////////////////
// addEngine
////////////////////////////////////////////////

bool ScriptManager::addEngine(ScriptEngine* engine)
{
  if (!engine)
    return false;

  auto engineLang = engine->getLanguage();
  if (engineLang.length() <= 0) {
    return false;
  }

  this->engineMap[engineLang] = std::unique_ptr<ScriptEngine>(engine);

  return true;
}

////////////////////////////////////////////////
// removeMethod
////////////////////////////////////////////////

bool ScriptManager::removeMethod(const std::string& name, Error* err)
{
  auto method = this->methodMap.getMethod(name);
  if (!method) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  return (this->methodMap.erase(name) == 1) ? true : false;
}

////////////////////////////////////////////////
// removeAllMethods
////////////////////////////////////////////////

bool ScriptManager::removeAllMethods(Error* error)
{
  this->methodMap.clear();
  return true;
}

////////////////////////////////////////////////
// execMethod
////////////////////////////////////////////////

bool ScriptManager::execMethod(const std::string& name, const Parameters* params, Parameters* results, Error* err)
{
  auto method = this->methodMap.getMethod(name);
  if (!method) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  auto scriptLang = method->getLanguage();
  if (scriptLang.length() <= 0) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  auto scriptEngine = this->engineMap.getEngine(scriptLang);
  if (!scriptEngine) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  lock();

  bool execResult = scriptEngine->run(method, params, results, err);

  unlock();

  return execResult;
}
