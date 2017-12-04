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

using namespace Foreman::Action;

#if defined(FOREMAN_SUPPORT_PYTHON)

////////////////////////////////////////////////
// PythonParameters
////////////////////////////////////////////////

PythonParameters::PythonParameters()
{
  this->dict_ = PyDict_New();
}

PythonParameters::~PythonParameters()
{
  Py_DECREF(this->dict_);
}

////////////////////////////////////////////////
// set
////////////////////////////////////////////////

bool PythonParameters::set(const Parameters* params)
{
  for (auto param : *params) {
    PythonParameter pyParam;
    if (!pyParam.set(param.get()))
      return false;
    if (PyDict_SetItemString(this->dict_, param->getName(), pyParam.getPyObject()) != 0)
      return false;
  }

  return true;
}

////////////////////////////////////////////////
// get
////////////////////////////////////////////////

bool PythonParameters::get(Parameters* params)
{
  PyObject *pyKey, *pyObj;
  Py_ssize_t pos = 0;

  while (PyDict_Next(this->dict_, &pos, &pyKey, &pyObj)) {
    PythonParameter pyParam;
    pyParam.setName(pyKey);
    if (!pyParam.setValue(pyObj))
      return false;
    Parameter* param;
    if (!pyParam.get(&param))
      return false;
    params->addParameter(param);
  }

  return true;
}

////////////////////////////////////////////////
// equals
////////////////////////////////////////////////

bool PythonParameters::equals(const Parameters* params)
{
  for (auto param : *params) {
    PyObject* pyObj = PyDict_GetItemString(this->dict_, param->getName());
    if (!pyObj)
      return false;
    PythonParameter pyParam;
    if (!pyParam.setName(param->getName()))
      return false;
    if (!pyParam.setValue(pyObj))
      return false;
    if (!pyParam.equals(param.get()))
      return false;
  }

  return true;
}

#endif
