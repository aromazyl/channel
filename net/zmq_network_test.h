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
#include "../message.h"
#include "../base/string_printf.hpp"

#include <gtest/gtest.h>
#include <glog/logging.h>

namespace net {

class ZMQNETWORKTesting : public ::testing::Test {
  public:
    void SetUp() {
      zmq_network = new ZMQ_NetWork;
      zmq_network->Init(NULL,NULL);
    }
    void TearDown() {
      zmq_network->Finalize();
      delete zmq_network;
    }
  private:
    ZMQ_NetWork* zmq_network;
};

TEST_F(ZMQNETWORKTesting, NetWorkSendingFunctionTest) {
  zmq_network->RegisterNetNode(0, "tcp://127.0.0.1");
  zmq_network->RegisterNetNode(1, "tcp://127.0.0.1");
  EXPECT_EQ(zmq_network->NodeNums(), 2);
  zmq_network->Bind(0, "5556");
  zmq_network->Connect(1, "5556");
  msg::MessagePtr msg_ptr;
  msg_ptr.reset(new msg::Message);
  msg_ptr->type = msg::PULL;
  msg_ptr->from = {0, 0, 0, 0, 0};
  msg_ptr->to = {1, 1, 1, 1 ,1};

  msg_ptr->blob.resize(1000);
  char test_buf[100] = "only for test";
  msg_ptr->blob.CopyFrom(test_buf, 100);
  LOG(INFO) << base::StringPrintf("blob:%s\n", msg_ptr->blob.data());
  msg_ptr->type = msg::MsgType(0);
  msg_ptr->from = {0, 0, 0, 0, 0};
  msg_ptr->to = {1, 1, 1, 1, 1};
  zmq_network->Send(1, msg_ptr);
  msg::MessagePtr recv_msg;
  zmq_network->Receive(recv_msg);
  LOG(INFO) << base::StringPrintf("type:%d, from:%s, to:%s, info:%s\n",
      recv_msg->type, recv_msg->from, recv_msg->to, recv_msg->blob.data());
}

}
