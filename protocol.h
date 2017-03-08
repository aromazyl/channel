/*
 * blob_protocal.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BLOB_PROTOCAL_H
#define BLOB_PROTOCAL_H

#include <glog/logging.h>
#include "./message.h"

namespace protocol {
  using namespace msg;

  template <typename MSG_TYPE> struct Decoder;

  template <typename Any> DecoderImpl;

  template <>
  struct DecoderImpl<Decoder<msg::REQUEST_ACTOR_TABLE_ACK>> {
    template <typename DecodeType>
    bool Apply(Message* message, DecodeType& type) const {
      if (!message) {
        LOG(ERROR) << "message cannot be null";
        return false;
      }

    }
  };

}

#endif /* !BLOB_PROTOCAL_H */
