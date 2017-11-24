/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_ACTION_PARAMETER_H_
#define _FOREMANCC_ACTION_PARAMETER_H_

#include <memory>
#include <string>
#include <vector>

#include <foreman/Platform.h>

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // Parameter
  ////////////////////////////////////////////////

  class Parameter {
public:
    Parameter();
    virtual ~Parameter();

    void setName(const std::string& name)
    {
      name_ = name;
    }

    const char* getName()
    {
      return name_.c_str();
    }

private:
protected:
    std::string name_;
  };

  ////////////////////////////////////////////////
  // Parameters
  ////////////////////////////////////////////////

  class Parameters : public std::vector<std::shared_ptr<Parameter>> {
public:
    Parameters();
    virtual ~Parameters();

    bool addParameter(Parameter* param);
    bool addParameter(const Parameter& param);
    bool addParameter(std::shared_ptr<Parameter> param);

    Parameter* getParameter(size_t n);
  };
}
}

#endif
