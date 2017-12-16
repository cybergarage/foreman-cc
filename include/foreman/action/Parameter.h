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

#include <boost/variant.hpp>

#include <foreman/Platform.h>

namespace Foreman {
namespace Action {

  ////////////////////////////////////////////////
  // Type
  ////////////////////////////////////////////////

  // Change the template arguments for boost::variant in Paramater if this changes
  enum ParameterType {
    IntegerType,
    RealType,
    StringType,
    BoolType,
    UnknownType
  };

  ////////////////////////////////////////////////
  // Parameter
  ////////////////////////////////////////////////

  class Parameter {
public:
    Parameter();
    Parameter(ParameterType type);
    virtual ~Parameter();

    void setName(const std::string& name)
    {
      name_ = name;
    }

    const char* getName() const
    {
      return name_.c_str();
    }

    bool isName(const std::string& name) const
    {
      return name_ == name;
    }

    bool isInteger() const { return isType(IntegerType); }
    bool isReal() const { return isType(RealType); }
    bool isString() const { return isType(StringType); }
    bool isBool() const { return isType(BoolType); }

    void setType(ParameterType type)
    {
      type_ = type;
    }

    ParameterType getType() const
    {
      return type_;
    }

    template <class T>
    void setValue(T value)
    {
      value_ = value;
      type_ = static_cast<ParameterType>(value_.which());
    }
    const auto getValue() const -> const decltype(value_)& { return value_; }

private:
    bool isType(ParameterType type) const
    {
      return value_.which() == type;
    }

protected:
    std::string name_;
    ParameterType type_;
    boost::variant<long, double, std::string, bool> value_;
  };

  ////////////////////////////////////////////////
  // Parameters
  ////////////////////////////////////////////////

  class Parameters : public std::vector<std::shared_ptr<Parameter> > {
public:
    Parameters();
    virtual ~Parameters();

    bool addParameter(Parameter* param);
    bool addParameter(const Parameter& param);
    bool addParameter(std::shared_ptr<Parameter> param);

    Parameter* getParameter(size_t n);
    Parameter* getParameter(const std::string& name);
  };
}
}
#endif
