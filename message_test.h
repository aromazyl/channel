/*
 * message_test.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#define public public
#define private public
#define protected public

#ifndef MESSAGE_TEST_H
#define MESSAGE_TEST_H

#include <gtest/gtest.h>
#include "./location.h"
#include "message.h"

namespace msg {

class MessageTest : public ::testing::Test {
  public:
    void SetUp() {
    }

    void TearDown() {}

  private:
};

TEST_F(MessageTest, SerializeTest) {
  Message message;
  message.type = 0;
  message.from = Location{1080, "255.255.252.255", kServerGroup, 15};
  message.to   = Location{1010, "250.222,202,1", kWorkerGroup, 0};
  char buf1[100] = "hello world";
  message.blob.CopyFrom(buf1, 100);
  void* buf = NULL; int size = 0;
  SerializeMessage(&message, &buf, &size);
  Message msg_get;
  DeserializeMessage(&msg_get, &buf, size);
  std::cout << DumpMessageInfo(msg_get);
}

}


#endif /* !MESSAGE_TEST_H */
