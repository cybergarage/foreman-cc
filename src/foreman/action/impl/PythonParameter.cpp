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
// PythonParameter
////////////////////////////////////////////////

PythonParameter::PythonParameter()
{
  this->obj_ = NULL;
}

PythonParameter::~PythonParameter()
{
  clear();
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

bool PythonParameter::clear()
{
  if (this->obj_) {
    Py_DECREF(this->obj_);
    this->obj_ = NULL;
  }

  return true;
}

////////////////////////////////////////////////
// setName
////////////////////////////////////////////////

bool PythonParameter::setName(PyObject* pyObj)
{
  if (!pyObj)
    return false;

  if (PyString_Check(pyObj)) {
    setName(PyString_AsString(pyObj));
    return true;
  }

  return false;
}

////////////////////////////////////////////////
// setValue
////////////////////////////////////////////////

bool PythonParameter::setValue(PyObject* pyObj)
{
  if (!pyObj)
    return false;

  if (PyInt_Check(pyObj)) {
    this->obj_ = pyObj;
    setType(IntegerType);
    return true;
  }

  return false;
}

////////////////////////////////////////////////
// set
////////////////////////////////////////////////

bool PythonParameter::set(const Parameter* param)
{
  if (!param)
    return false;

  clear();

  setName(param->getName());

  // Integer

  if (param->isInteger()) {
    auto iparam = dynamic_cast<const Integer*>(param);
    if (!iparam)
      return false;
    auto pyObj = PyInt_FromLong(iparam->getValue());
    if (!pyObj)
      return false;
    if (!setValue(pyObj)) {
      Py_DECREF(pyObj);
      return false;
    }

    return true;
  }

  return false;
}

////////////////////////////////////////////////
// get
////////////////////////////////////////////////

bool PythonParameter::get(Parameter** param)
{
  // Integer

  if (isInteger() && PyInt_Check(this->obj_)) {
    auto iparam = new Integer();
    if (!iparam)
      return false;
    iparam->setValue(PyInt_AsLong(this->obj_));
    setType(IntegerType);
    *param = iparam;
    return true;
  }

  return false;
}

////////////////////////////////////////////////
// equals
////////////////////////////////////////////////

bool PythonParameter::equals(const Parameter* param)
{
  if (getType() != param->getType())
    return false;

  // Integer

  if (param->isInteger()) {
    auto iparam = dynamic_cast<const Integer*>(param);
    if (!iparam)
      return false;
    if (PyInt_AsLong(this->obj_) != iparam->getValue())
      return false;
    return true;
  }

  return true;
}

#endif
