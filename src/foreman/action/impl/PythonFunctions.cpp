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

#include <foreman/Client.h>
#include <foreman/Const.h>
#include <foreman/action/impl/GlobalObject.h>
#include <foreman/action/impl/Python.h>
#include <foreman/common/Error.h>
#include <foreman/log/Log.h>
#include <string.h>

/****************************************
 * See: Python Documentation - Extending Python with C or C++
 * https://docs.python.org/3/extending/extending.html
 ****************************************/

/****************************************
 * foreman_python_setregistry
 ****************************************/

PyObject* foreman_python_setregister(PyObject* self, PyObject* args)
{
  const char *key, *val;

  if (!PyArg_ParseTuple(args, "ss", &key, &val)) {
    Py_RETURN_NONE;
  }

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (!store) {
    Py_RETURN_NONE;
  }

  Foreman::Register::Object obj;
  obj.setKey(key);
  obj.setData(val);

  Foreman::Error err;
  bool isSuccess = store->setObject(&obj, &err);

  FOREMAN_LOG_DEBUG("SET KEY : %s = %s (%d)", key, val, int(isSuccess));

  return Py_BuildValue("i", isSuccess);
}

/****************************************
 * foreman_python_getregistry
 ****************************************/

PyObject* foreman_python_getregister(PyObject* self, PyObject* args)
{
  const char* key;

  if (!PyArg_ParseTuple(args, "s", &key)) {
    Py_RETURN_NONE;
  }

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (!store) {
    Py_RETURN_NONE;
  }

  Foreman::Register::Object obj;
  Foreman::Error err;
  bool isSuccess = store->getObject(key, &obj, &err);

  const char* regData = NULL;
  if (isSuccess) {
    regData = obj.getData();
  }

  FOREMAN_LOG_DEBUG("GET KEY : %s = %s (%d)", key, (regData ? regData : ""), int(isSuccess));

  return Py_BuildValue("s", regData);
}

/****************************************
 * foreman_python_removeregistry
 ****************************************/

PyObject* foreman_python_removeregister(PyObject* self, PyObject* args)
{
  const char* key;

  if (!PyArg_ParseTuple(args, "s", &key)) {
    Py_RETURN_NONE;
  }

  auto store = Foreman::Action::GetGlobalRegisterStore();
  if (!store) {
    Py_RETURN_NONE;
  }

  Foreman::Error err;
  bool isSuccess = store->removeObject(key, &err);

  FOREMAN_LOG_DEBUG("REMOVE KEY : %s (%d)", key, int(isSuccess));

  return Py_BuildValue("i", isSuccess);
}

/****************************************
 * foreman_python_string2jsonobject
 ****************************************/

#define FOREMANCC_PYTHON_PARSEJSON_METHOD "_foreman_python_parsejson"
#define FOREMANCC_PYTHON_PARSEJSON_MODULE FOREMANCC_PRODUCT_NAME "_internal"

#if !defined(DEBUG)
#define FOREMANCC_PYTHON_PARSEJSON_METHOD_CODE        \
  "import json\n"                                     \
  "def " FOREMANCC_PYTHON_PARSEJSON_METHOD "(str):\n" \
  "    return json.loads(str)\n"
#else
#define FOREMANCC_PYTHON_PARSEJSON_METHOD_CODE        \
  "import json\n"                                     \
  "def " FOREMANCC_PYTHON_PARSEJSON_METHOD "(str):\n" \
  "    jsonObj = json.loads(str)\n"                   \
  "    print(jsonObj)\n"                              \
  "    return jsonObj\n"
#endif

static bool foreman_python_string2jsonobject(const std::string& jsonStr, PyObject** pyObj, Foreman::Error* err)
{
  static PyObject* pyJsonModule = NULL;
  static PyObject* pyJsonFunc = NULL;

  *pyObj = NULL;

  if (jsonStr.size() <= 0) {
    return true;
  }

  if (!pyJsonFunc) {
    PyObject* pSource = Py_CompileString(FOREMANCC_PYTHON_PARSEJSON_METHOD_CODE, FOREMANCC_PYTHON_PARSEJSON_METHOD, Py_file_input);
    if (!pSource) {
      foreman_python_getlasterror(err);
      return false;
    }

    auto moduleName = Foreman::Action::PythonEngineGetUserModuleName("foreman_python_string2jsonobject");
    pyJsonModule = PyImport_ExecCodeModule((char*)moduleName.c_str(), pSource);
    Py_XDECREF(pSource);
    if (!pyJsonModule) {
      foreman_python_getlasterror(err);
      return false;
    }

    pyJsonFunc = PyObject_GetAttrString(pyJsonModule, FOREMANCC_PYTHON_PARSEJSON_METHOD);
    if (!pyJsonFunc || !PyCallable_Check(pyJsonFunc)) {
      foreman_python_getlasterror(err);
      Py_XDECREF(pyJsonModule);
      pyJsonModule = NULL;
      return false;
    }
  }

  // See
  // Python/C API Reference Manual- Reference Count Details
  // https://docs.python.org/2.0/api/refcountDetails.html

  PyObject* pArgs = Py_BuildValue("(s)", jsonStr.c_str());
  PyObject* pResults = PyObject_CallObject(pyJsonFunc, pArgs);
  Py_XDECREF(pArgs);

  *pyObj = pResults;

  return true;
}

/****************************************
 * foreman_python_requestquery
 ****************************************/

static PyObject* foreman_python_requestquery(PyObject* self, Foreman::Client& client, const char* query)
{
  Foreman::Error err;

  // Query

  std::string jsonRes;
  FOREMAN_LOG_DEBUG("%s", query);
  if (!client.query(query, &jsonRes)) {
    Py_RETURN_NONE;
  }
  FOREMAN_LOG_DEBUG("%s", jsonRes.c_str());

  // Parse the JSON response

  PyObject* resObj;

  if (!foreman_python_string2jsonobject(jsonRes, &resObj, &err)) {
    Py_RETURN_NONE;
  }

  if (!resObj) {
    resObj = PyDict_New();
  }

  PyObject* retObj = Py_BuildValue("O", resObj);
  Py_XDECREF(resObj);
  return retObj;
}

/****************************************
 * foreman_python_executequery
 ****************************************/

PyObject* foreman_python_executequery(PyObject* self, PyObject* args)
{
  Foreman::Error err;

  const char* query;
  if (!PyArg_ParseTuple(args, "s", &query)) {
    Py_RETURN_NONE;
  }

  Foreman::Client client;

  return foreman_python_requestquery(self, client, query);
}

/****************************************
 * foreman_python_postquery
 ****************************************/

PyObject* foreman_python_postquery(PyObject* self, PyObject* args)
{
  Foreman::Error err;

  const char* host;
  const char* query;
  int port;
  if (!PyArg_ParseTuple(args, "sis", &host, &port, &query)) {
    Py_RETURN_NONE;
  }

  Foreman::Client client;
  client.setHost(host);
  client.setPort(port);

  return foreman_python_requestquery(self, client, query);
}

/****************************************
 * foreman_python_log
 ****************************************/

PyObject* foreman_python_log_core(PyObject* self, const char* log_message, const char* log_level)
{
  size_t outputters;
  if (strcmp(log_level, "fatal") == 0) {
    outputters = Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::FATAL, "%s", log_message);
  }
  else if (strcmp(log_level, "error") == 0) {
    outputters = Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::ERROR, "%s", log_message);
  }
  else if (strcmp(log_level, "warn") == 0) {
    outputters = Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::WARN, "%s", log_message);
  }
  else if (strcmp(log_level, "debug") == 0) {
    outputters = Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::DBG, "%s", log_message);
  }
  else if (strcmp(log_level, "trace") == 0) {
    outputters = Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::TRACE, "%s", log_message);
  }
  else {
    outputters = Foreman::Log::Logger::GetSharedInstance()->message(Foreman::Log::INFO, "%s", log_message);
  }

  return Py_BuildValue("l", outputters);
}

PyObject* foreman_python_log(PyObject* self, PyObject* args)
{
  Foreman::Error err;

  const char* log_message;
  const char* log_level;
  if (!PyArg_ParseTuple(args, "ss", &log_message, &log_level)) {
    Py_RETURN_NONE;
  }

  return foreman_python_log_core(self, log_message, log_level);
}

PyObject* foreman_python_log_fatal(PyObject* self, PyObject* args)
{
  Foreman::Error err;

  const char* log_message;
  if (!PyArg_ParseTuple(args, "s", &log_message)) {
    Py_RETURN_NONE;
  }

  return foreman_python_log_core(self, log_message, "fatal");
}

PyObject* foreman_python_log_error(PyObject* self, PyObject* args)
{
  Foreman::Error err;

  const char* log_message;
  if (!PyArg_ParseTuple(args, "s", &log_message)) {
    Py_RETURN_NONE;
  }

  return foreman_python_log_core(self, log_message, "error");
}

PyObject* foreman_python_log_warn(PyObject* self, PyObject* args)
{
  Foreman::Error err;

  const char* log_message;
  if (!PyArg_ParseTuple(args, "s", &log_message)) {
    Py_RETURN_NONE;
  }

  return foreman_python_log_core(self, log_message, "warn");
}

PyObject* foreman_python_log_info(PyObject* self, PyObject* args)
{
  Foreman::Error err;

  const char* log_message;
  if (!PyArg_ParseTuple(args, "s", &log_message)) {
    Py_RETURN_NONE;
  }

  return foreman_python_log_core(self, log_message, "info");
}

PyObject* foreman_python_log_debug(PyObject* self, PyObject* args)
{
  Foreman::Error err;

  const char* log_message;
  if (!PyArg_ParseTuple(args, "s", &log_message)) {
    Py_RETURN_NONE;
  }

  return foreman_python_log_core(self, log_message, "debug");
}

PyObject* foreman_python_log_trace(PyObject* self, PyObject* args)
{
  Foreman::Error err;

  const char* log_message;
  if (!PyArg_ParseTuple(args, "s", &log_message)) {
    Py_RETURN_NONE;
  }

  return foreman_python_log_core(self, log_message, "trace");
}

/****************************************
 * Python Modules
 ****************************************/

static PyMethodDef gForemanPythonMethods[] = {
  { FOREMANCC_SYSTEM_FUNCTION_SETREGISTER, foreman_python_setregister, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_GETREGISTER, foreman_python_getregister, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_REMOVEREGISTER, foreman_python_removeregister, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_EXECUTEQUERY, foreman_python_executequery, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_POSTQUERY, foreman_python_postquery, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_LOG, foreman_python_log, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_LOG_FATAL, foreman_python_log_fatal, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_LOG_ERROR, foreman_python_log_error, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_LOG_WARN, foreman_python_log_warn, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_LOG_INFO, foreman_python_log_info, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_LOG_DEBUG, foreman_python_log_debug, METH_VARARGS, "" },
  { FOREMANCC_SYSTEM_FUNCTION_LOG_TRACE, foreman_python_log_trace, METH_VARARGS, "" },
  { NULL, NULL, 0, NULL }
};

PyMethodDef* Foreman::Action::GetPythonSystemMethods()
{
  return gForemanPythonMethods;
}

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef gForemanPythonModule = {
  PyModuleDef_HEAD_INIT,
  FOREMANCC_PRODUCT_NAME, /* m_name */
  FOREMANCC_PRODUCT_NAME, /* m_doc */
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
