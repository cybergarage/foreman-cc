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
  // Type
  ////////////////////////////////////////////////

  enum ParameterType { UnknownType,
    IntegerType,
    RealType,
    StringType,
    BoolType };

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
      return (name_.compare(name) == 0) ? true : false;
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

private:
    bool isType(ParameterType type) const
    {
      return (type_ == type) ? true : false;
    }

protected:
    std::string name_;
    ParameterType type_;
  };

  class Integer : public Parameter {
public:
    Integer()
        : Parameter(IntegerType)
    {
    }
    ~Integer() {}
    void setValue(long value) { value_ = value; }
    long getValue() const { return value_; }

private:
    long value_;
  };

  class Real : public Parameter {
public:
    Real()
        : Parameter(RealType)
    {
    }
    ~Real() {}
    void setValue(double value) { value_ = value; }
    double getValue() const { return value_; }

private:
    double value_;
  };

  class String : public Parameter {
public:
    String()
        : Parameter(StringType)
    {
    }
    ~String() {}
    void setValue(const std::string& value) { value_ = value; }
    const std::string& getValue() const { return value_; }

private:
    std::string value_;
  };

  class Bool : public Parameter {
public:
    Bool()
        : Parameter(BoolType)
    {
    }
    ~Bool() {}
    void setValue(bool value) { value_ = value; }
    bool getValue() const { return value_; }

private:
    bool value_;
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
    Parameter* getParameter(const std::string& name);
  };
}
}

#endif
