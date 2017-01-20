/*
 * server_test.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "../net/zmq_network.h"

using namespace net;

int client_run() {
  auto client = new ZMQ_NetWork;

  client->Init(NULL, NULL);
  client->RegisterNetNode(0, "tcp://127.0.0.1");
  client->Connect(0, "55555");

  msg::MessagePtr mmsg(new msg::Message);
  mmsg->type = msg::MsgType(0);
  mmsg->from = 0;
  mmsg->to = 0;
  char buf[10] = "i love u";
  mmsg->blob.resize(10);
  mmsg->blob.CopyFrom(buf, sizeof(buf));
  srand(time(NULL));
  while (true) {
    mmsg->type = msg::MsgType(rand() % 4);
    mmsg->from = msg::MsgType(rand());
    mmsg->to = msg::MsgType(rand());
    client->Send(0, mmsg);
    printf("send_msg:type:%d, from:%d, to:%d, data:%s\n",
        mmsg->type, mmsg->from, mmsg->to, mmsg->blob.data());

    usleep(1000 * 1000);
  }

  client->Finalize();

  return 0;
}
