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

class ProtocolTest : public ::testing::Test {
  public:
    void SetUp() {}
    void TearDown() {}
};

TEST_F(ProtocolTest, EmptyProtocol) {
  Encoder<DEFAULT> encoder;
  Decoder<DEFAULT> decoder;

}

TEST_F(ProtocolTest, BcastProtocol) {
}

TEST_F(ProtocolTest, HeartBeatProtocol) {
}

TEST_F(ProtocolTest, PullProtocol) {}

TEST_F(ProtocolTest, PushProtocol) {}

TEST_F(ProtocolTest, RegisterProtocol) {}

#endif /* !PROTOCOL_TEST_H */
