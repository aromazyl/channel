/*
 * register_protocol.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef REGISTER_PROTOCOL_H
#define REGISTER_PROTOCOL_H

// register table support for register  worder and server's location
namespace protocol {
template <>
struct Encoder<BCAST_TABLE> {
  bool Apply(const Location& from, const Location& to,
      std::unordered_set<Location>& locs, )
};
template <>
struct Decoder<BCAST_TABLE>
}

#endif /* !REGISTER_PROTOCOL_H */
