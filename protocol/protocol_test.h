/*
 * protocol_test.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PROTOCOL_TEST_H
#define PROTOCOL_TEST_H

#define public public
#define private public
#define protected public

#include <gtest/gtest.h>
#include "message.h"
#include "protocols.h"
#include "location.h"

class ProtocolTest : public ::testing::Test {
  public:
    void SetUp() {
      from.rank = 0;
      from.port = 1234;
      from.ip   = 1024332;
      from.type = kServerGroup;
      from.type_id = 0;
      to.rank = 2;
      to.port = 1234;
      to.ip   = 12312312;
      to.type = kWorkerGroup;
    }
    void TearDown() {}

  public:
    Location from;
    Location to;
};

TEST_F(ProtocolTest, BasicTest) {
}

TEST_F(ProtocolTest, EmptyProtocol) {
}

TEST_F(ProtocolTest, BcastProtocol) {
}

TEST_F(ProtocolTest, HeartBeatProtocol) {
}

TEST_F(ProtocolTest, PullProtocol) {}

TEST_F(ProtocolTest, PushProtocol) {}

TEST_F(ProtocolTest, RegisterProtocol) {}
TEST_F(ProtocolTest, CommandProtocol) {}


#endif /* !PROTOCOL_TEST_H */
