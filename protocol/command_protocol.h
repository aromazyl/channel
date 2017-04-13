/*
 * comm_protocol.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef COMM_PROTOCOL_H
#define COMM_PROTOCOL_H

#include "message.h"
#include "protocol/protocol.h"

namespace protocol {
using namespace msg;

static int Command = INT_MAX;

template <MsgType CMD>
struct Encoder {
  static bool Apply(const Location& from, const Location& to,
      Message** msg) {
    if (!*msg) *msg = new Message;
    EncodeAddressInfo<CMD>(from, to, *msg);
    return true;
  }
};

template <MsgType CMD>
struct Decoder {
  static bool Apply(const Message& msg, Location* from, Location* to) {
    if (!from || !to) {
      LOG(ERROR) << "from or to is empyt, command " <<
        CMD << " decode failure.";
      return false;
    }
    DecodeAddressInfo(msg, from, to);
    return true;
  }
};

}


#endif /* !COMM_PROTOCOL_H */
