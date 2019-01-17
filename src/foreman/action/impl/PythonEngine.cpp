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

#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>

#include <foreman/Const.h>
#include <foreman/action/impl/Python.h>
#include <foreman/common/Errors.h>

const std::string Foreman::Action::PythonEngine::LANGUAGE = FOREMANCC_ACTION_SCRIPT_ENGINE_PYTHON;
const std::string Foreman::Action::PythonEngine::MODULE = FOREMANCC_PRODUCT_NAME;
const std::string Foreman::Action::PythonEngine::USER_MODULE = FOREMANCC_PRODUCT_NAME "_user";
const std::string Foreman::Action::PythonEngine::SYSTEM_MODULE = FOREMANCC_PRODUCT_NAME "_system";

////////////////////////////////////////////////
// PythonEngineInitialize
////////////////////////////////////////////////

bool Foreman::Action::PythonEngineInitialize()
{
  if (Py_IsInitialized())
    return true;

  Py_Initialize();

#if PY_MAJOR_VERSION >= 3
  PyModule_Create(GetPythonSystemModule());
#else
  Py_InitModule(FOREMANCC_PRODUCT_NAME, GetPythonSystemMethods());
#endif

  return true;
}

////////////////////////////////////////////////
// PythonEngineIsInitialized
////////////////////////////////////////////////

bool Foreman::Action::PythonEngineIsInitialized()
{
  return Py_IsInitialized() ? true : false;
}

////////////////////////////////////////////////
// PythonEngineFinalize
////////////////////////////////////////////////

bool Foreman::Action::PythonEngineFinalize()
{
  if (!Py_IsInitialized())
    return true;

  // See :
  // Python/C API Reference Manual » Initializing and finalizing the interpreter
  // https://docs.python.org/2.7/c-api/init.html
  // Some extensions may not work properly if their initialization routine is called
  // more than once; this can happen if an application calls Py_Initialize() and Py_Finalize() more than once.

  //Py_Finalize();

  return true;
}

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Foreman::Action::PythonEngine::PythonEngine()
    : ScriptEngine(LANGUAGE)
{
  if (PythonEngineInitialize())
    return;
}

////////////////////////////////////////////////
// Destructor
////////////////////////////////////////////////

Foreman::Action::PythonEngine::~PythonEngine()
{
  PythonEngineFinalize();
}

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

bool Foreman::Action::PythonEngine::compile(Method* method, Error* err)
{
  auto pyScript = dynamic_cast<PythonMethod*>(method);
  if (!pyScript) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    getLastPythonError(err);
    return false;
  }

  if (!pyScript->compile(err)) {
    getLastPythonError(err);
    return false;
  }

  return true;
}

////////////////////////////////////////////////
// run
////////////////////////////////////////////////

bool Foreman::Action::PythonEngine::run(Method* method, const Parameters* params, Parameters* results, Error* err)
{
  // See
  // Python Documentation - Extending Python with C or C++
  // https://docs.python.org/3/extending/extending.html
  // Python Documentation - Embedding Python in Another Application¶
  // https://docs.python.org/2.7/extending/embedding.html#embedding-python-in-another-application

  auto pyScript = dynamic_cast<PythonMethod*>(method);
  if (!pyScript) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    getLastPythonError(err);
    return false;
  }

  if (!pyScript->isCompiled()) {
    if (!pyScript->compile(err)) {
      getLastPythonError(err);
      return false;
    }
  }

  // Set input parametershttps://docs.python.org/3/extending/extending.html

  PythonParameters pInParams;
  if (!pInParams.set(params)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    getLastPythonError(err);
    return false;
  }

  // Set outnput parameters

  PythonParameters pOutParams;

  // Exec method

  // See
  // Python/C API Reference Manual- Reference Count Details
  // https://docs.python.org/2.0/api/refcountDetails.html

  PyObject* pArgs = Py_BuildValue("(OO)", pInParams.getPyObject(), pOutParams.getPyObject());
  PyObject* pResults = PyObject_CallObject(pyScript->getFuncObject(), pArgs);
  Py_XDECREF(pArgs);

  if (!pResults) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    getLastPythonError(err);
    return false;
  }

  if ((pResults != Py_None) && (pResults != Py_True)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INVALID_REQUEST);
    PyObject* errMsg = PyObject_Repr(pResults);
    if (errMsg) {
      err->setDetailMessage(PyString_AsString(errMsg));
      Py_XDECREF(errMsg);
    }
    Py_XDECREF(pResults);
    return false;
  }

  if (!pOutParams.get(results)) {
    FOREMANCC_ERROR_SET_ERRORNO(err, ERROR_INTERNAL_ERROR);
    getLastPythonError(err);
    Py_XDECREF(pResults);
    return false;
  }

  Py_XDECREF(pResults);

  return true;
}

////////////////////////////////////////////////
// getLastPythonError
////////////////////////////////////////////////

bool Foreman::Action::PythonEngine::getLastPythonError(Error* err) const
{
  return foreman_python_getlasterror(err);
}

bool foreman_python_getlasterror(Foreman::Error* error)
{
  std::stringstream pyErrMsg;

  PyObject *ptype, *pvalue, *ptraceback;
  PyErr_Fetch(&ptype, &pvalue, &ptraceback);

  if (ptype) {
    PyObject* utfStr = PyUnicode_AsUTF8String(ptype);
    if (utfStr) {
      auto errStr = PyString_AsString(utfStr);
      if (errStr) {
        pyErrMsg << errStr;
        Py_XDECREF(errStr);
      }
      Py_XDECREF(utfStr);
    }
  }

  if (pvalue) {
    PyObject* utfStr = PyUnicode_AsUTF8String(pvalue);
    if (utfStr) {
      auto errStr = PyString_AsString(utfStr);
      if (errStr) {
        if (ptype) {
          pyErrMsg << " (";
        }
        pyErrMsg << errStr;
        Py_XDECREF(errStr);
        if (ptype) {
          pyErrMsg << ")";
        }
      }
      Py_XDECREF(utfStr);
    }
  }

  error->setMessage(pyErrMsg.str());

#if defined(DEBUG)
  if (ptype)
    PyObject_Print(ptype, stdout, 0);
  if (pvalue)
    PyObject_Print(pvalue, stdout, 0);
  if (ptraceback)
    PyObject_Print(ptraceback, stdout, 0);
#endif

  if (ptype)
    Py_XDECREF(ptype);
  if (pvalue)
    Py_XDECREF(pvalue);
  if (ptraceback)
    Py_XDECREF(ptraceback);

  PyErr_Clear();

  return true;
}

#endif
