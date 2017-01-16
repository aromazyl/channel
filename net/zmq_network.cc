/*
 * zmq_network.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "zmq_network.h"


namespace net {
  void ZMQ_NetWork::Init(int* argc, char** argv) {
    context_ = zmq_ctx_new();
    zmq_ctx_set(context_, ZMQ_MAX_SOCKETS, 256);
  }
  void ZMQ_NetWork::Finalize() {
    delete context_;
  }
}
