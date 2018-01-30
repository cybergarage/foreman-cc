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
#include <foreman/action/impl/GlobalObject.h>

#if defined(FOREMAN_SUPPORT_PYTHON)

/****************************************
 * foreman_python_setregistry
 ****************************************/

PyObject* foreman_python_setregistry(PyObject* self, PyObject* args)
{
  const char *key, *val;

  if (!PyArg_ParseTuple(args, "ss", &key, &val))
    return NULL;

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (!store)
    return NULL;

  Foreman::Register:: Object obj;
  obj.setKey(key);
  obj.setData(val);
  
  Foreman::Error err;
  bool isSuccess = store->setObject(&obj, &err);

  return Py_BuildValue("i", isSuccess);
}

/****************************************
 * foreman_python_getregistry
 ****************************************/

PyObject* foreman_python_getregistry(PyObject* self, PyObject* args)
{
  const char *key;

  if (!PyArg_ParseTuple(args, "s", &key))
    return NULL;

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (!store)
    return NULL;

  Foreman::Register:: Object obj;
  Foreman::Error err;
  bool isSuccess = store->getObject(key, &obj, &err);

  return Py_BuildValue("s", (isSuccess ? obj.getData() : ""));
}

/****************************************
 * foreman_python_removeregistry
 ****************************************/

PyObject* foreman_python_removeregistry(PyObject* self, PyObject* args)
{
  const char* key;

  if (!PyArg_ParseTuple(args, "s", &key))
    return NULL;

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (!store)
    return NULL;

  Foreman::Error err;
  bool isSuccess = store->removeObject(key, &err);

  return Py_BuildValue("i", isSuccess);
}

/****************************************
 * Python Modules
 ****************************************/

static PyMethodDef gForemanPythonMethods[] = {
  { "foreman_setregister", foreman_python_setregistry, METH_VARARGS, "" },
  { "foreman_getregister", foreman_python_getregistry, METH_VARARGS, "" },
  { "foreman_removeregister", foreman_python_removeregistry, METH_VARARGS, "" },
  { NULL, NULL, 0, NULL }
};

PyMethodDef* Foreman::Action::GetPythonSystemMethods()
{
  return gForemanPythonMethods;
}

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef gForemanPythonModule = {
  PyModuleDef_HEAD_INIT,
  FOREMAN_PRODUCT_NAME, /* m_name */
  FOREMAN_PRODUCT_NAME, /* m_doc */
  -1, /* m_size */
  gForemanPythonMethods, /* m_methods */
  NULL, /* m_reload */
  NULL, /* m_traverse */
  NULL, /* m_clear */
  NULL, /* m_free */
};

PyModuleDef* Foreman::Action::GetPythonSystemModule()
{
  return &gForemanPythonModule;
}
#endif

#endif
