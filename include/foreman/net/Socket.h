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

#include <uhttp/net/Socket.h>

namespace Foreman {

class Socket : public uHTTP::Socket {

  public:
  Socket();
  ~Socket();
};
}

#endif
