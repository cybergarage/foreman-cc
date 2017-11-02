/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/common/Error.h>
#include <foreman/foreman-c.h>

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
  if (!e && !msg)
    return false;
  ((Foreman::Error*)(e))->setMessage(msg);
  return true;
}

////////////////////////////////////////////////
// foreman_error_setcode
////////////////////////////////////////////////

bool foreman_error_setcode(ForemanError* e, double code)
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
  if (!e && !msg)
    return false;
  ((Foreman::Error*)(e))->setDetailMessage(msg);
  return true;
}

////////////////////////////////////////////////
// foreman_error_setdetailcode
////////////////////////////////////////////////

bool foreman_error_setdetailcode(ForemanError* e, double code)
{
  if (!e)
    return false;
  ((Foreman::Error*)(e))->setDetailCode(code);
  return true;
}

////////////////////////////////////////////////
// foreman_error_getmessage
////////////////////////////////////////////////

bool foreman_error_getmessage(ForemanError* e, const char** msg)
{
  if (!e && !msg)
    return false;
  *msg = ((Foreman::Error*)(e))->getMessage();
  return true;
}

////////////////////////////////////////////////
// foreman_error_getcode
////////////////////////////////////////////////

bool foreman_error_getcode(ForemanError* e, int* code)
{
  if (!e && !code)
    return false;
  *code = ((Foreman::Error*)(e))->getCode();
  return true;
}

////////////////////////////////////////////////
// foreman_error_getdetailmessage
////////////////////////////////////////////////

bool foreman_error_getdetailmessage(ForemanError* e, const char** msg)
{
  if (!e && !msg)
    return false;
  *msg = ((Foreman::Error*)(e))->getDetailMessage();
  return true;
}

////////////////////////////////////////////////
// foreman_error_getdetailcode
////////////////////////////////////////////////

bool foreman_error_getdetailcode(ForemanError* e, int* code)
{
  if (!e && !code)
    return false;
  *code = ((Foreman::Error*)(e))->getDetailCode();
  return true;
}
