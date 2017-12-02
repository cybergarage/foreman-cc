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
#include <foreman/action/Script.h>
#include <foreman/action/impl/Python.h>

#include <string.h>

const int Foreman::Action::Script::ENCODING_NONE = FOREMANCC_ACTION_SCRIPT_ENCORDING_NONE;
const int Foreman::Action::Script::ENCODING_BASE64 = FOREMANCC_ACTION_SCRIPT_ENCORDING_BASE64;

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

Foreman::Action::Script* Foreman::Action::Script::CreateScript(const std::string& lang)
{
#if defined(FOREMAN_SUPPORT_PYTHON)
  if (lang.compare(Foreman::Action::PythonEngine::LANGUAGE) == 0)
    return new Foreman::Action::PythonScript();
#endif

  return new Script(lang);
}

////////////////////////////////////////////////
// compile
////////////////////////////////////////////////

Foreman::Action::Script::Script(const std::string& lang)
{
  init();
  this->language = lang;
}

Foreman::Action::Script::~Script()
{
  if (this->code) {
    free(this->code);
  }
}

////////////////////////////////////////////////
// init
////////////////////////////////////////////////

void Foreman::Action::Script::init()
{
  this->language = "";
  this->code = NULL;
  this->codeLen = 0;
  setEncording(ENCODING_NONE);
}

////////////////////////////////////////////////
// setCode
////////////////////////////////////////////////

bool Foreman::Action::Script::setCode(const byte* code, size_t codeLen)
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

bool Foreman::Action::Script::setCode(const std::string code)
{
  return setCode((const byte*)code.c_str(), (code.length() + 1));
}

////////////////////////////////////////////////
// isBinaryCode
////////////////////////////////////////////////

bool Foreman::Action::Script::isBinaryCode()
{
  for (size_t n = 0; n < this->codeLen; n++) {
    byte c = this->code[n];
    if ((c < 0x20) || (0x7E < c)) {
      return true;
    }
  }
  return false;
}
