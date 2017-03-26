/*
 * heart_beat_protocol.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef HEART_BEAT_PROTOCOL_H
#define HEART_BEAT_PROTOCOL_H

#include "protocol/protocol.h"

namespace protocol {
  using namespace msg;

  template <>
  struct Encoder<HEART_BEAT> {
    bool Apply(const Location& from, const Location& to, Message** msg) {
      if (*msg) return false;
      *msg = new Message;
      (*msg)->from = from;
      (*msg)->to = to;
      (*msg)->type = HEART_BEAT;
      return true;
    }
  };

  template <>
    struct Encoder<HEART_BEAT> {
      bool Apply(const Message& msg, Location* from, Location* to) {
        if (!from || !to) {
          LOG(ERROR) << "heart beat decode from or to is empty";
          return false;
        }

        *from = msg.from;
        *to = msg.to;
        return true;
      }
    };
}


#endif /* !HEART_BEAT_PROTOCOL_H */
