/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMANCC_PLATFORM_H_
#define _FOREMANCC_PLATFORM_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#elif defined(__APPLE__)
#define HAVE_UUID_UUID_H 1
#endif

#if defined(__APPLE__)
#define FOREMAN_SUPPORT_PYTHON 1
#define HAVE_PYTHON_PYTHON_H 1
#define FOREMAN_ENABLE_ALGLIB 1
#endif

#if !defined(byte)
typedef unsigned char byte;
#endif

#if defined(FOREMAN_ENABLE_ALGLIB)
#define FOREMAN_ENABLE_ANALYZER 1
#endif

#endif
