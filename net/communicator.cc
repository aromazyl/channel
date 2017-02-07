/*
 * communicator.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "communicator.h"

#include "./zmq_network.h"
#include "../conf/configure.h"

namespace network {
  void Communicator::PreStart() {
    net_ = new ZMQ_NetWork;
    CHECK(Configure::Get()->IsExistConf("NETWORK_TABLE"));
    char ip_port[40];
    char id;
  }
}
