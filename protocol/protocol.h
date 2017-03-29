/*
 * blob_protocal.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BLOB_PROTOCAL_H
#define BLOB_PROTOCAL_H

#include <glog/logging.h>
#include "message.h"

namespace protocol {
using namespace msg;

template <MsgType type> struct Decoder;

template <MsgType type> struct Encoder;

inline void DecodeAddressInfo(const Message& msg, Location* from, Location* to) {
  *from = msg.from;
  *to = msg.to;
}

template <MsgType type>
inline void EncodeAddressInfo(const Location& from, const Location& to, Message& msg) {
  msg.from = from;
  msg.to = to;
  msg.type = type;
}

}

#endif /* !BLOB_PROTOCAL_H */
