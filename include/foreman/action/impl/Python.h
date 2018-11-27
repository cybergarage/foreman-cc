/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_PYTHON_H_
#define _FOREMANCC_ACTION_PYTHON_H_

#include <foreman/Platform.h>
#include <foreman/action/Engine.h>

#if defined(FOREMAN_SUPPORT_PYTHON)

#if defined(HAVE_PYTHON_H)
#include <Python.h>
#elif defined(HAVE_PYTHON_PYTHON_H)
#include <Python/Python.h>
#elif defined(__APPLE__)
#include <Python/Python.h>
#else
#include <Python.h>
#endif

namespace Foreman {
namespace Action {

  PyMethodDef* GetPythonSystemMethods();

#if PY_MAJOR_VERSION >= 3
  PyModuleDef* GetPythonSystemModule();
#endif

  ////////////////////////////////////////////////
  // PythonParameter
  ////////////////////////////////////////////////

  class PythonParameter : public Parameter {
public:
    PythonParameter();
    ~PythonParameter();

    bool setName(const std::string& name);
    bool setName(PyObject* pyObj);
    bool setValue(PyObject* pyObj);

    bool set(const Parameter* param);
    bool get(Parameter** param);

    bool equals(const Parameter* param);

    PyObject* getPyObject() const;

private:
    bool clear();

private:
    PyObject* obj_;
  };

  ////////////////////////////////////////////////
  // PythonParameters
  ////////////////////////////////////////////////

  class PythonParameters {
public:
    PythonParameters();
    ~PythonParameters();

    bool set(const Parameters* params);
    bool get(Parameters* params);

    bool equals(const Parameters* params);

    PyObject* getPyObject()
    {
      return dict_;
    }

private:
    PyObject* dict_;
  };

  ////////////////////////////////////////////////
  // PythonMethod
  ////////////////////////////////////////////////

  class PythonMethod : public Method {
public:
    PythonMethod();
    ~PythonMethod();

    bool clear();

    bool compile(Error* error);
    bool isCompiled() const;

    PyObject* getModuleObject()
    {
      return module_;
    }

    PyObject* getFuncObject()
    {
      return func_;
    }

private:
    PyObject* module_;
    PyObject* func_;
  };

  ////////////////////////////////////////////////
  // PythonEngine
  ////////////////////////////////////////////////

  class PythonEngine : public ScriptEngine {

public:
    static const std::string LANGUAGE;
    static const std::string MODULE;

public:
    PythonEngine();
    ~PythonEngine();

    bool compile(Method* method, Error* error);
    bool run(Method* method, const Parameters* params, Parameters* results, Error* error);

private:
    bool setLastDetailError(Error* error) const;
  };
}
}

#endif

#endif
