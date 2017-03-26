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
}

#endif /* !BLOB_PROTOCAL_H */
