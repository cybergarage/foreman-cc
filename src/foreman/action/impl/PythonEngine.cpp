/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>

#include <foreman/Const.h>
#include <foreman/action/impl/Python.h>
#include <foreman/common/Errors.h>

#if defined(FOREMAN_SUPPORT_PYTHON)

const std::string Foreman::Action::PythonEngine::LANGUAGE = "python";
const std::string Foreman::Action::PythonEngine::MODULE = FOREMANCC_PRODUCT_NAME;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Foreman::Action::PythonEngine::PythonEngine()
    : ScriptEngine(LANGUAGE)
{
  if (!Py_IsInitialized()) {
    Py_Initialize();
#if PY_MAJOR_VERSION >= 3
#else
#endif
  }
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

Foreman::Action::PythonEngine::~PythonEngine()
{
  if (Py_IsInitialized()) {
    Py_Finalize();
  }
}

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

bool Foreman::Action::PythonEngine::compile(Method* method, Error* err)
{
  auto pyScript = dynamic_cast<PythonMethod*>(method);
  if (!pyScript) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    setLastDetailError(err);
    return false;
  }

  return pyScript->compile(err);
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

bool Foreman::Action::PythonEngine::run(Method* method, const Parameters* params, Parameters* results, Error* err)
{
  // See :
  // 5. Embedding Python in Another Application¶
  // https://docs.python.org/2.7/extending/embedding.html#embedding-python-in-another-application

  auto pyScript = dynamic_cast<PythonMethod*>(method);
  if (!pyScript) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    setLastDetailError(err);
    return false;
  }

  if (!pyScript->isCompiled()) {
    if (!pyScript->compile(err)) {
      setLastDetailError(err);
      return false;
    }
  }

  // Set input parameters

  PythonParameters pInParams;
  if (!pInParams.set(params)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    setLastDetailError(err);
    return false;
  }

  // Set outnput parameters

  PythonParameters pOutParams;

  // Exec method

  PyObject* pArgs = PyTuple_New(2);
  if (!pArgs) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    setLastDetailError(err);
    return false;
  }

  PyTuple_SetItem(pArgs, 0, pInParams.getPyObject());
  PyTuple_SetItem(pArgs, 1, pOutParams.getPyObject());

  PyObject* pResults = PyObject_CallObject(pyScript->getFuncObject(), pArgs);
  if (!pResults) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    setLastDetailError(err);
    Py_DECREF(pArgs);
    return false;
  }

  if ((pResults != Py_None) && (pResults != Py_True)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    PyObject* errMsg = PyObject_Repr(pResults);
    if (errMsg) {
      err->setDetailMessage(PyString_AsString(errMsg));
      Py_DECREF(errMsg);
    }
    Py_DECREF(pArgs);
    return false;
  }

  if (!pOutParams.get(results)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    setLastDetailError(err);
    Py_DECREF(pArgs);
    return false;
  }

  Py_DECREF(pArgs);

  return true;
}

////////////////////////////////////////////////
// getLastError
////////////////////////////////////////////////

bool Foreman::Action::PythonEngine::setLastDetailError(Error* error) const
{
  PyObject *ptype, *pvalue, *ptraceback;
  PyErr_Fetch(&ptype, &pvalue, &ptraceback);
  error->setDetailMessage(PyString_AsString(pvalue));

#if defined(DEBUG)
  PyObject_Print(ptype, stdout, 0);
  PyObject_Print(pvalue, stdout, 0);
  PyObject_Print(ptraceback, stdout, 0);
#endif

  return true;
}

#endif
