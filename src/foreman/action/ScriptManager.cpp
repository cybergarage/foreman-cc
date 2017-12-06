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
#include <foreman/common/Errors.h>

////////////////////////////////////////////////
// ScriptManager
////////////////////////////////////////////////

Foreman::Action::ScriptManager::ScriptManager()
{
}

Foreman::Action::ScriptManager::~ScriptManager()
{
}

////////////////////////////////////////////////
// setScript
////////////////////////////////////////////////

bool Foreman::Action::ScriptManager::addMethod(Method* method)
{
  if (!method)
    return false;

  auto name = method->getName();
  if (name.length() <= 0) {
    return false;
  }

  auto currentScript = this->methods.getMethod(name);
  if (currentScript) {
    delete currentScript;
  }

  this->methods[name] = method;

  return true;
}

////////////////////////////////////////////////
// addEngine
////////////////////////////////////////////////

bool Foreman::Action::ScriptManager::addEngine(ScriptEngine* engine)
{
  if (!engine)
    return false;

  auto engineLang = engine->getLanguage();
  if (engineLang.length() <= 0) {
    return false;
  }

  auto currentEngine = this->engines.getEngine(engineLang);
  if (currentEngine) {
    delete currentEngine;
  }

  this->engines[engineLang] = engine;

  return true;
}

////////////////////////////////////////////////
// addMethod
////////////////////////////////////////////////

bool Foreman::Action::ScriptManager::addMethod(const std::string& name, const std::string& lang, const std::string& code, int encodeType, Error* err)
{
  if (code.length() <= 0) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  ScriptEngine* scriptEngine = this->engines.getEngine(lang);
  if (!scriptEngine) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  Method* method = Foreman::Action::Method::CreateMethod(lang);
  if (!method) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }
  method->setName(name);
  method->setCode(code);
  method->setEncording(encodeType);

  if (!scriptEngine->compile(method, err)) {
    delete method;
    return false;
  }

  if (!addMethod(method)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    delete method;
    return false;
  }

  return true;
}

////////////////////////////////////////////////
// removeScript
////////////////////////////////////////////////

bool Foreman::Action::ScriptManager::removeMethod(const std::string& name, Error* err)
{
  auto method = this->methods.getMethod(name);
  if (!method) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  return (this->methods.erase(name) == 1) ? true : false;
}

bool Foreman::Action::ScriptManager::execMethod(const std::string& name, const Parameters* params, Parameters* results, Error* err)
{
  auto method = this->methods.getMethod(name);
  if (!method) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  auto scriptLang = method->getLanguage();
  if (scriptLang.length() <= 0) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  auto scriptEngine = this->engines.getEngine(scriptLang);
  if (!scriptEngine) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  return scriptEngine->run(method, params, results, err);
}
