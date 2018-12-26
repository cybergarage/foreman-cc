/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Platform.h>

#if defined(FOREMAN_SUPPORT_PYTHON)

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
  if (func_) {
    Py_DECREF(func_);
    func_ = NULL;
  }

  if (module_) {
    Py_DECREF(module_);
    module_ = NULL;
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

  auto methodCode = (const char*)getCode();
  if (!methodCode) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  auto methodName = getName().c_str();
  PyObject* pSource = Py_CompileString(methodCode, methodName, Py_file_input);
  if (!pSource) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    return false;
  }

  auto moduleName = PythonEngine::USER_MODULE.c_str();
  this->module_ = PyImport_ExecCodeModule((char*)moduleName, pSource);
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
#endif
