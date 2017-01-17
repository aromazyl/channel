/*
 * zmq_network_test.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#define public public
#define private public
#define protected public

#include "zmq_network.h"

#include <gtest/gtest.h>

namespace net {

class ZMQNETWORKTesting : public ::testing::Test {
  public:
    void SetUp() {
      zmq_network = new ZMQ_NetWork;
    }
    void TearDown() {
      delete zmq_network;
    }
  private:
    ZMQ_NetWork* zmq_network;
};

TEST_F(ZMQNETWORKTesting, InitalZMQ_NETWORK_LOCAL) {
}

TEST_F(ZMQNETWORKTesting, FinalizeZMQ_NETWORK_LOCAL) {
}

TEST_F(ZMQNETWORKTesting, BindZMQ_NETWORK_LOCAL) {
}

TEST_F(ZMQNETWORKTesting, ConnectZMQ_NETWORK_LOCAL) {
}

TEST_F(ZMQNETWORKTesting, SendZMQ_NETWORK_LOCAL) {
}

TEST_F(ZMQNETWORKTesting, ReceiveZMQ_NETWORK_LOCAL) {
}

TEST_F(ZMQNETWORKTesting, NodeNumsZMQ_NETWORK_LOCAL) {
}

TEST_F(ZMQNETWORKTesting, RegisterNetNodeZMQ_NETWORK_LOCAL) {
}
}
