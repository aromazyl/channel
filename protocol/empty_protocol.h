/*
 * empty_protocol.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef EMPTY_PROTOCOL_H
#define EMPTY_PROTOCOL_H

#include "protocol/protocol.h"

namespace protocol {
  using namespace msg;
  
  template <>
  struct Encoder<DEFAULT> {
    bool Apply(const Location& from, const Location& to, void* buf, int size, Message** msg) {
      if (*msg) return false;
      *msg = new Message;
      (*msg)->from = from;
      (*msg)->to = to;
      (*msg)->blob.resize(size);
      (*msg)->blob.CopyFrom(buf, size);
      (*msg)->type = DEFAULT;
      return true;
    }
  };

  struct Decoder<DEFAULT> {
    bool Apply(const Message& msg, Location* from, Location* to, blob::Blob* blob) {
      if (!from) {
        LOG(ERROR) << "default message decode failure, from is empty";
        return false;
      }

      if (!to) {
        LOG(ERROR) << "default message decode failure, to is empty";
        return false;
      }

      if (!blob) {
        LOG(ERROR) << "default message decode failure, blob is empty";
        return false;
      }

      *from = msg.from;
      *to = msg.to;
      *blob = msg.blob;
      return true;
    }
  };
}

#endif /* !EMPTY_PROTOCOL_H */
