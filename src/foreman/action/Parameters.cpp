/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/action/Parameter.h>
#include <foreman/util/Util.h>

using namespace Foreman::Action;

////////////////////////////////////////////////
// Parameters
////////////////////////////////////////////////

Parameters::Parameters()
{
}

Parameters::~Parameters() {}

////////////////////////////////////////////////
// addParameters
////////////////////////////////////////////////

bool Parameters::addParameter(Parameter* params)
{
  return addParameter(std::shared_ptr<Foreman::Action::Parameter>(params));
}

////////////////////////////////////////////////
// addParameters
////////////////////////////////////////////////

bool Parameters::addParameter(const Parameter& params)
{
  return addParameter(new Foreman::Action::Parameter(params));
}

////////////////////////////////////////////////
// addParameters
////////////////////////////////////////////////

bool Parameters::addParameter(std::shared_ptr<Foreman::Action::Parameter> params)
{
  push_back(params);
  return true;
}

////////////////////////////////////////////////
// getParameter
////////////////////////////////////////////////

Parameter* Parameters::getParameter(size_t n)
{
  if ((size() - 1) < n)
    return NULL;
  return at(n).get();
}

////////////////////////////////////////////////
// getParameter
////////////////////////////////////////////////

Parameter* Parameters::getParameter(const std::string& name)
{
  for (auto param = begin(); param != end(); ++param) {
    if ((*param)->isName(name))
      return (*param).get();
  }
  return NULL;
}
