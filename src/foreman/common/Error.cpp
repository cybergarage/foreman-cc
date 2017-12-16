/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/common/Error.h>
#include <foreman/common/Errors.h>
#include <string.h>

Foreman::Error::Error()
{
  initialize();
  this->code = 0;
}

Foreman::Error::Error(int code)
{
  initialize();
  this->code = code;
}

Foreman::Error::Error(int code, const std::string& message)
{
  initialize();
  this->code = code;
  this->message = message;
}

Foreman::Error::Error(int code, const std::string& message, int detailCode, const std::string& detailMessage)
{
  initialize();
  this->code = code;
  this->message = message;
  this->detailCode = detailCode;
  this->detailMessage = detailMessage;
}

void Foreman::Error::initialize()
{
  this->code = 0;
  this->detailCode = 0;
}

Foreman::Error::~Error()
{
}

bool Foreman::Error::isError()
{
  if (0 < this->code)
    return true;
  return false;
}

void Foreman::Error::setErrorNo(int err_no)
{
  setCode(err_no);
  setMessage(Foreman::ErrorCodeToMessage(err_no));
}

bool Foreman::Error::equals(const Error& other) const
{
  if (this->getCode() != other.getCode())
    return false;

  if (this->message.compare(other.getMessage()) != 0)
    return false;

  return true;
}
