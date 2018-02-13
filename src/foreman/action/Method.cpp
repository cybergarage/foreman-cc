/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Const.h>
#include <foreman/action/Method.h>
#include <foreman/action/impl/Python.h>

#include <string.h>

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

Foreman::Action::Method* Foreman::Action::Method::CreateMethod(const std::string& lang)
{
#if defined(FOREMAN_SUPPORT_PYTHON)
  if (lang.compare(Foreman::Action::PythonEngine::LANGUAGE) == 0)
    return new Foreman::Action::PythonMethod();
#endif

  return new Method(lang);
}

////////////////////////////////////////////////
// Method
////////////////////////////////////////////////

Foreman::Action::Method::Method()
{
  init();
}

Foreman::Action::Method::Method(const std::string& lang)
{
  init();
  this->language = lang;
}

Foreman::Action::Method::~Method()
{
  if (this->code) {
    free(this->code);
  }
}

////////////////////////////////////////////////
// init
////////////////////////////////////////////////

void Foreman::Action::Method::init()
{
  this->language = "";
  this->code = NULL;
  this->codeLen = 0;
}

////////////////////////////////////////////////
// setCode
////////////////////////////////////////////////

bool Foreman::Action::Method::setCode(const byte* code, size_t codeLen)
{
  if (this->code) {
    free(this->code);
  }
  this->codeLen = 0;

  this->code = (byte*)malloc(codeLen);
  if (!this->code)
    return false;

  memcpy(this->code, code, codeLen);
  this->codeLen = codeLen;

  return true;
}

bool Foreman::Action::Method::setCode(const std::string code)
{
  return setCode((const byte*)code.c_str(), (code.length() + 1));
}

////////////////////////////////////////////////
// isBinaryCode
////////////////////////////////////////////////

bool Foreman::Action::Method::isBinaryCode()
{
  for (size_t n = 0; n < this->codeLen; n++) {
    byte c = this->code[n];
    if ((c < 0x20) || (0x7E < c)) {
      return true;
    }
  }
  return false;
}
