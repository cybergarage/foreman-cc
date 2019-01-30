/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/log/Outputter.h>

using namespace Foreman::Log;

////////////////////////////////////////////////
// OutputterList
////////////////////////////////////////////////

OutputterList::OutputterList()
{
}

OutputterList::~OutputterList()
{
}

////////////////////////////////////////////////
// addOutputter
////////////////////////////////////////////////

void OutputterList::addOutputter(Outputter* outputter)
{
  std::unique_ptr<Outputter> outputterPtr(outputter);
  this->push_back(std::move(outputterPtr));
}
