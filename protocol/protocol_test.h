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
#include "base/string_printf.hpp"
#include "meta_template.h"

namespace msg {
using namespace protocol;
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
  Message emsg;
  emsg.type = DEFAULT;
  emsg.from = from;
  emsg.to = to;
  DecodeAddressInfo(emsg, &from, &to);
  EXPECT_EQ(emsg.from, from);
  EXPECT_EQ(emsg.to, to);
  __print(sizeof_emsg_to, sizeof(emsg.to));
  __print(sizeof_int_5, sizeof(int) * 5);
  static_assert(sizeof(emsg.to) == sizeof(int) * 5, "emsg size is not equal to int size");
}

TEST_F(ProtocolTest, EmptyProtocol) {
  Message* msg = NULL;
  void* buf = (void*)malloc(sizeof(char) * 27);
  int size = sizeof(char) * 27;
  memcpy(buf, "abcdefghijklmnopqrstuvwxyz", sizeof(char) * 27);
  EXPECT_TRUE(Encoder<DEFAULT>::Apply(from, to, buf, size, &msg));
  Location from1, to1;
  blob::Blob blob;
  EXPECT_TRUE(Decoder<DEFAULT>::Apply(*msg, &from1, &to1, &blob));
  EXPECT_EQ(from, from1);
  EXPECT_EQ(to, to1);
  EXPECT_TRUE(!strcmp((char*)blob.data(), (char*)(msg->blob.data())));
  delete msg;
}

TEST_F(ProtocolTest, BcastProtocol) {
  std::vector<Location> locations = {
    {0, 123, 0, 0, 0}, {1, 12, 1, 1, 1},
    {12, 3, 11, 1231121, 123121}, {12, 0, INT_MAX, INT_MAX, INT_MAX}
  };
  std::vector<Location> reply_locs;
  Message* msg = NULL;
  EXPECT_TRUE(Encoder<BCAST_TABLE>::Apply(from, to, locations, &msg));
  Location from1, to1;
  EXPECT_TRUE(Decoder<BCAST_TABLE>::Apply(*msg, &from1, &to1, &reply_locs));
  EXPECT_EQ(from, from1);
  EXPECT_EQ(to, to1);
  delete msg;
}

TEST_F(ProtocolTest, HeartBeatProtocol) {
  Message* msg = NULL;
  EXPECT_TRUE(Encoder<HEART_BEAT>::Apply(from, to, &msg));
  Location from1, to1;
  EXPECT_TRUE(Decoder<HEART_BEAT>::Apply(*msg, &from1, &to1));
  EXPECT_EQ(from, from1);
  EXPECT_EQ(to, to1);
}

TEST_F(ProtocolTest, PullProtocol) {
  Message* msg = NULL;
  std::vector<uint64_t> keys = {1,2,3,4,5,-1,-2};
  std::vector<uint64_t> keys1;
  EXPECT_TRUE(Encoder<PULL>::Apply<uint64_t>(from, to, keys, &msg));
  Location from1, to1;
  EXPECT_TRUE(Decoder<PULL>::Apply<uint64_t>(*msg, &from1, &to1, &keys1));
  EXPECT_EQ(from, from1);
  EXPECT_EQ(to, to1);
  EXPECT_EQ(keys, keys1);
}

TEST_F(ProtocolTest, PushProtocol) {
  Encoder<PUSH>::
}

TEST_F(ProtocolTest, RegisterProtocol) {
}

TEST_F(ProtocolTest, CommandProtocol) {
}
}


#endif /* !PROTOCOL_TEST_H */
