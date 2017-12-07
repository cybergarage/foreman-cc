/******************************************************************
 *
 * Foreman for C
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/Method.h>
#include <foreman/action/action-c.h>

using namespace Foreman::Action;

////////////////////////////////////////////////
// foreman_action_method_new
////////////////////////////////////////////////

ForemanActionMethod* foreman_action_method_new()
{
  return new Method();
}

////////////////////////////////////////////////
// foreman_action_method_delete
////////////////////////////////////////////////

bool foreman_action_method_delete(ForemanActionMethod* method)
{
  if (!method)
    return false;
  delete (Method*)method;
  return true;
}

////////////////////////////////////////////////
// foreman_action_method_setname
////////////////////////////////////////////////

bool foreman_action_method_setname(ForemanActionMethod* method, const char* name)
{
  if (!method || !name)
    return false;
  return ((Method*)method)->setName(name);
}

////////////////////////////////////////////////
// foreman_action_method_getname
////////////////////////////////////////////////

bool foreman_action_method_getname(ForemanActionMethod* method, const char** name)
{
  if (!method || !name)
    return false;
  *name = ((Method*)method)->getName().c_str();
  return true;
}

////////////////////////////////////////////////
// foreman_action_method_setlanguage
////////////////////////////////////////////////

bool foreman_action_method_setlanguage(ForemanActionMethod* method, const char* lang)
{
  if (!method)
    return false;
  return ((Method*)method)->setLanguage(lang);
}

////////////////////////////////////////////////
// foreman_action_method_getlanguage
////////////////////////////////////////////////

bool foreman_action_method_getlanguage(ForemanActionMethod* method, const char** lang)
{
  if (!method || !lang)
    return false;
  *lang = ((Method*)method)->getLanguage().c_str();
  return true;
}

////////////////////////////////////////////////
// foreman_action_method_setcode
////////////////////////////////////////////////

bool foreman_action_method_setcode(ForemanActionMethod* method, const byte* code, size_t codeLen)
{
  if (!method || !code)
    return false;
  return ((Method*)method)->setCode(code, codeLen);
}

////////////////////////////////////////////////
// foreman_action_method_setstringcode
////////////////////////////////////////////////

bool foreman_action_method_setstringcode(ForemanActionMethod* method, const char* code)
{
  if (!method || !code)
    return false;
  return ((Method*)method)->setCode(code);
}

////////////////////////////////////////////////
// foreman_action_method_getcode
////////////////////////////////////////////////

bool foreman_action_method_getcode(ForemanActionMethod* method, const byte** code)
{
  if (!method || !code)
    return false;
  *code = ((Method*)method)->getCode();
  return true;
}

////////////////////////////////////////////////
// foreman_action_method_getcodelength
////////////////////////////////////////////////

bool foreman_action_method_getcodelength(ForemanActionMethod* method, size_t* size)
{
  if (!method || !size)
    return false;
  *size = ((Method*)method)->getCodeLength();
  return true;
}

////////////////////////////////////////////////
// foreman_action_method_getstringcode
////////////////////////////////////////////////

bool foreman_action_method_getstringcode(ForemanActionMethod* method, const char** code)
{
  if (!method || !code)
    return false;
  *code = ((Method*)method)->getStringCode();
  return true;
}

////////////////////////////////////////////////
// foreman_action_method_setencoding
////////////////////////////////////////////////

bool foreman_action_method_setencoding(ForemanActionMethod* method, int encType)
{
  if (!method)
    return false;
  return ((Method*)method)->setEncoding(encType);
}

////////////////////////////////////////////////
// foreman_action_method_getencoding
////////////////////////////////////////////////

bool foreman_action_method_getencoding(ForemanActionMethod* method, int* encType)
{
  if (!method || !encType)
    return false;
  *encType = ((Method*)method)->getEncoding();
  return true;
}

////////////////////////////////////////////////
// foreman_action_method_isbase64encoded
////////////////////////////////////////////////

bool foreman_action_method_isbase64encoded(ForemanActionMethod* method)
{
  if (!method)
    return false;
  return ((Method*)method)->isBase64Encoded();
}

