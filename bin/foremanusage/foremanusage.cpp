/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) Satoshi Konno 2017
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include <sys/resource.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
  struct rusage usage;

  getrusage(RUSAGE_SELF, &usage);

  return EXIT_SUCCESS;
}
