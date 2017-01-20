/*
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include "../message.h"
#include "../net/zmq_network.h"

using namespace net;

int server_run() {
  auto server = new ZMQ_NetWork;

  server->Init(NULL, NULL);
  server->RegisterNetNode(0, "tcp://127.0.0.1");
  server->Bind(0, "55555");

  msg::MessagePtr msg;

  int turn = 0;
  while (true) {
    printf("receiving turn:%d\n", turn ++);
    server->Receive(msg);
    printf("recv_msg:type:%d, from:%d, to:%d, data:%s\n",
        msg->type, msg->from, msg->to, msg->blob.data());
  }

  server->Finalize();
  return 0;
}
