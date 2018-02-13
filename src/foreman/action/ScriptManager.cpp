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

  auto name = method->getName();
  if (name.length() <= 0) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  auto currentScript = this->methodMap.getMethod(name);
  if (currentScript) {
    delete currentScript;
  }

  this->methodMap[name] = method;

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

  auto currentEngine = this->engineMap.getEngine(engineLang);
  if (currentEngine) {
    delete currentEngine;
  }

  this->engineMap[engineLang] = engine;

  return true;
}

////////////////////////////////////////////////
// addMethod
////////////////////////////////////////////////

bool ScriptManager::addMethod(const std::string& name, const std::string& lang, const std::string& code, Error* err)
{
  if (code.length() <= 0) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  ScriptEngine* scriptEngine = this->engineMap.getEngine(lang);
  if (!scriptEngine) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  Method* method = Method::CreateMethod(lang);
  if (!method) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }
  method->setName(name);
  method->setCode(code);

  if (!scriptEngine->compile(method, err)) {
    delete method;
    return false;
  }

  if (!addMethod(method, err)) {
    delete method;
    return false;
  }

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

  return scriptEngine->run(method, params, results, err);
}
