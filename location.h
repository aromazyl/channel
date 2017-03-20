/*
 * location.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef LOCATION_H
#define LOCATION_H

// location info for actors
#include "base/string_printf.hpp"

enum ActorType {
  kServerGroup,
  kWorkerGroup,
};

struct Location {
  // process rank
  int rank;
  // process port
  int port;

  char ip[15];
  ActorType type;
  int type_id;
};

inline
std::string DumpLocationInfo(const Location& loc) {
  return base::StringPrintf("port:%d, ip:%s, actortype:%s, typeid:%d",
      loc.port, loc.ip, loc.type, loc.type_id);
}


#endif /* !LOCATION_H */
