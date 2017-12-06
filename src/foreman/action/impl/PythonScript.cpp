/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/impl/Python.h>
#include <foreman/common/Errors.h>

////////////////////////////////////////////////
// PythonMethod
////////////////////////////////////////////////

Foreman::Action::PythonMethod::PythonMethod()
    : Foreman::Action::Method(Foreman::Action::PythonEngine::LANGUAGE)
{
  module_ = NULL;
  func_ = NULL;
}

Foreman::Action::PythonMethod::~PythonMethod()
{
  clear();
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool Foreman::Action::PythonMethod::clear()
{
  if (module_) {
    Py_DECREF(module_);
    module_ = NULL;
  }

  if (func_) {
    Py_DECREF(func_);
    func_ = NULL;
  }

  return true;
}

////////////////////////////////////////////////
// isCompiled
////////////////////////////////////////////////

bool Foreman::Action::PythonMethod::isCompiled() const
{
  if (!module_ || !func_)
    return false;

  return true;
}

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

bool Foreman::Action::PythonMethod::compile(Error* err)
{
  if (!clear()) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    return false;
  }

  auto methodName = getName().c_str();
  char moduleName[64];
  snprintf(moduleName, sizeof(moduleName), "%s-%s", PythonEngine::MODULE.c_str(), methodName);

  PyObject* pSource = Py_CompileString((const char*)getCode(), methodName, Py_file_input);
  if (!pSource) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  this->module_ = PyImport_ExecCodeModuleEx((char*)moduleName, pSource, (char*)methodName);
  Py_DECREF(pSource);
  if (!(this->module_)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  this->func_ = PyObject_GetAttrString(this->module_, methodName);
  if (!(this->func_) || !PyCallable_Check(this->func_)) {
    clear();
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  return true;
}
