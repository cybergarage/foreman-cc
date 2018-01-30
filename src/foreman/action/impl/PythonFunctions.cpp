/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

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

  bool isSuccess = foreman_local_node_setregistry(node, key, val);

  return Py_BuildValue("i", isSuccess);
}

/****************************************
 * foreman_python_getregistry
 ****************************************/

PyObject* foreman_python_getregistry(PyObject* self, PyObject* args)
{
  const char *key, *val;

  if (!PyArg_ParseTuple(args, "s", &key))
    return NULL;

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (!store)
    return NULL;

  RoundRegistry* reg = foreman_local_node_getregistry(node, key);
  if (!foreman_registry_getstring(reg, &val)) {
    reg = NULL;
  }

  return Py_BuildValue("s", (reg ? val : ""));
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

  bool isSuccess = foreman_local_node_removeregistry(node, key);

  return Py_BuildValue("i", isSuccess);
}

/****************************************
 * Python Modules
 ****************************************/

static PyMethodDef gForemanPythonMethods[] = {
  { foreman_SYSTEM_METHOD_SET_REGISTRY, foreman_python_setregistry, METH_VARARGS, "" },
  { foreman_SYSTEM_METHOD_GET_REGISTRY, foreman_python_getregistry, METH_VARARGS, "" },
  { foreman_SYSTEM_METHOD_REMOVE_REGISTRY, foreman_python_removeregistry, METH_VARARGS, "" },
  { NULL, NULL, 0, NULL }
};

PyMethodDef* Foreman::Action::GetPythonSystemMethods();
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

PyModuleDef* Foreman::Action::GetPythonSystemModule();
{
  return &gForemanPythonModule;
}
#endif

#endif
