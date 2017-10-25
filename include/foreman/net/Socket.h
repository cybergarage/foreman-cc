/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _FOREMAN_NET_SOCKET_H_
#define _FOREMAN_NET_SOCKET_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(FOREMAN_ENABLE_UHTTPCC)
#include <uhttp/net/Socket.h>
#endif

namespace Foreman {

#if defined(FOREMAN_ENABLE_UHTTPCC)

class Socket : public uHTTP::Socket {

  public:
  Socket();
  ~Socket();
};

#endif
}

#endif
