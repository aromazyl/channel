/*
 * location.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef LOCATION_H
#define LOCATION_H

// location info for actors
#include <stdio.h>
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

  int ip;
  // Actor Type
  int type;
  int type_id;

  bool operator==(const Location& loc) const {
    return this->rank == loc.rank &&
      this->port == loc.port &&
      this->ip == loc.ip &&
      this->type == loc.type &&
      this->type_id == loc.type_id;
  }
};

namespace std {
  template <> struct hash<Location> {
    size_t operator()(const Location& loc) const {
      size_t hash = 23;
      hash = hash * 31 + loc.rank;
      hash = hash * 31 + loc.port;
      hash = hash * 31 + loc.ip;
      hash = hash * 31 + loc.type;
      hash = hash * 31 + loc.type_id;
      return hash;
    }
  };
}

inline
std::string PrintIp(int ip) {
  return base::StringPrintf("%d.%d.%d.%d",
      ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff);
}

inline
int RPrintIp(const std::string& ip) {
  int a, b, c, d;
  sscanf(ip.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d);
  return (a << 24) + (b << 16) + (c << 8) + d;
}

inline
std::string DumpLocationInfo(const Location& loc) {
  return base::StringPrintf("port:%d, ip:%s, actortype:%s, typeid:%d",
      loc.port, loc.ip, loc.type, loc.type_id);
}


#endif /* !LOCATION_H */
