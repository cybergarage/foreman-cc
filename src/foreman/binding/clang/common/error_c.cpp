/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/common/Error.h>
#include <foreman/common/common-c.h>

using namespace Foreman;

////////////////////////////////////////////////
// foreman_error_new
////////////////////////////////////////////////

ForemanError* foreman_error_new()
{
  return new Error();
}

////////////////////////////////////////////////
// foreman_error_delete
////////////////////////////////////////////////

bool foreman_error_delete(ForemanError* e)
{
  if (!e)
    return false;
  delete (Error*)e;
  return true;
}

////////////////////////////////////////////////
// foreman_error_setmessage
////////////////////////////////////////////////

bool foreman_error_setmessage(ForemanError* e, const char* msg)
{
  if (!e || !msg)
    return false;
  ((Foreman::Error*)(e))->setMessage(msg);
  return true;
}

////////////////////////////////////////////////
// foreman_error_setcode
////////////////////////////////////////////////

bool foreman_error_setcode(ForemanError* e, int code)
{
  if (!e)
    return false;
  ((Foreman::Error*)(e))->setCode(code);
  return true;
}

////////////////////////////////////////////////
// foreman_error_setdetailmessage
////////////////////////////////////////////////

bool foreman_error_setdetailmessage(ForemanError* e, const char* msg)
{
  if (!e || !msg)
    return false;
  ((Foreman::Error*)(e))->setDetailMessage(msg);
  return true;
}

////////////////////////////////////////////////
// foreman_error_setdetailcode
////////////////////////////////////////////////

bool foreman_error_setdetailcode(ForemanError* e, int code)
{
  if (!e)
    return false;
  ((Foreman::Error*)(e))->setDetailCode(code);
  return true;
}

////////////////////////////////////////////////
// foreman_error_setlineno
////////////////////////////////////////////////

bool foreman_error_setlineno(ForemanError* e, int lineno)
{
  if (!e)
    return false;
  ((Foreman::Error*)(e))->setLineNo(lineno);
  return true;
}

////////////////////////////////////////////////
// foreman_error_setfilename
////////////////////////////////////////////////

bool foreman_error_setfilename(ForemanError* e, const char* name)
{
  if (!e || !name)
    return false;
  ((Foreman::Error*)(e))->setFileName(name);
  return true;
}

////////////////////////////////////////////////
// foreman_error_setfuncname
////////////////////////////////////////////////

bool foreman_error_setfuncname(ForemanError* e, const char* name)
{
  if (!e || !name)
    return false;
  ((Foreman::Error*)(e))->setFuncName(name);
  return true;
}

////////////////////////////////////////////////
// foreman_error_getmessage
////////////////////////////////////////////////

bool foreman_error_getmessage(ForemanError* e, const char** msg)
{
  if (!e || !msg)
    return false;
  *msg = ((Foreman::Error*)(e))->getMessage();
  return true;
}

////////////////////////////////////////////////
// foreman_error_getcode
////////////////////////////////////////////////

bool foreman_error_getcode(ForemanError* e, int* code)
{
  if (!e || !code)
    return false;
  *code = ((Foreman::Error*)(e))->getCode();
  return true;
}

////////////////////////////////////////////////
// foreman_error_getdetailmessage
////////////////////////////////////////////////

bool foreman_error_getdetailmessage(ForemanError* e, const char** msg)
{
  if (!e || !msg)
    return false;
  *msg = ((Foreman::Error*)(e))->getDetailMessage();
  return true;
}

////////////////////////////////////////////////
// foreman_error_getdetailcode
////////////////////////////////////////////////

bool foreman_error_getdetailcode(ForemanError* e, int* code)
{
  if (!e || !code)
    return false;
  *code = ((Foreman::Error*)(e))->getDetailCode();
  return true;
}

////////////////////////////////////////////////
// foreman_error_getlineno
////////////////////////////////////////////////

bool foreman_error_getlineno(ForemanError* e, int* lineno)
{
  if (!e)
    return false;
  *lineno = ((Foreman::Error*)(e))->getLineNo();
  return true;
}

////////////////////////////////////////////////
// foreman_error_getfilename
////////////////////////////////////////////////

bool foreman_error_getfilename(ForemanError* e, const char** name)
{
  if (!e || !name)
    return false;
  *name = ((Foreman::Error*)(e))->getFileName();
  return true;
}

////////////////////////////////////////////////
// foreman_error_getfuncname
////////////////////////////////////////////////

bool foreman_error_getfuncname(ForemanError* e, const char** name)
{
  if (!e || !name)
    return false;
  *name = ((Foreman::Error*)(e))->getFuncName();
  return true;
}

////////////////////////////////////////////////
// foreman_error_isinternalerror
////////////////////////////////////////////////

bool foreman_error_isinternalerror(ForemanError* e)
{
  if (!e)
    return true;
  return ((Foreman::Error*)(e))->isInternalError();
}
