/******************************************************************
 *
 * Foreman for C++
 *
 * Copyright (C) 2017 Satoshi Konno. All rights reserved.
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <foreman/Platform.h>
#include <foreman/util/UUID.h>

#if defined(HAVE_LIBUUID)
#include <uuid/uuid.h>
#endif

////////////////////////////////////////////////
// CreateUUID
////////////////////////////////////////////////

bool Foreman::CreateUUID(std::string& buf)
{
#if defined(HAVE_LIBUUID)
  uuid_t uuid;
  char uuidStr[64 /* > 36+1 */];
  uuid_generate(uuid);
  uuid_unparse_upper(uuid, uuidStr);
  buf = uuidStr;
#else
  // TODO : Implement the following random algorithm of RFC-4122.
  // https://tools.ietf.org/html/rfc4122#page-14
  // 4.4.  Algorithms for Creating a UUID from Truly Random or Pseudo-Random Numbers
  return false;
#endif

  return true;
}
