/*
 * zmq_network.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "zmq_network.h"
#include <glog/logging.h>


namespace net {
  void ZMQ_NetWork::Init(int* argc, char** argv) {
    context_ = zmq_ctx_new();
    zmq_ctx_set(context_, ZMQ_MAX_SOCKETS, 256);
  }

  void ZMQ_NetWork::Finalize() {
    zmq_ctx_destory(context_);
  }

  void ZMQ_NetWork::Bind(int rank) {
    CHECK(context_) << "Init ZMQ context firstly!";
    CHECK(this->node_table_.count(rank)) << "rank:" << rank
      << " does not registed";
    if (node_table_[rank]->receiver) return;
    node_table_[rank]->receiver = zmq_socket(context_, ZMQ_DEALER);
    CHECK(!zmq_bind(node_table_[rank]->receiver, node_table_[rank]->addr.c_str()))
      << "rank:" << rank << " bind failure, addr:" << node_table_[rank]->addr;
  }
  
  void ZMQ_NetWork::Connect(int rank, const std::string& port) {
    CHECK(context_) << "Init ZMQ context firstly!";
    CHECK(this->node_table_.count(rank)) << "rank:" << rank
      << " does not registed";
    if (node_table_[rank]->sender) return;
    node_table_[rank]->sender = zmq_socket(context_, ZMQ_DEALER);
    std::string ip_port = node_table_[rank]->addr + ":" + port;
    CHECK(!zmq_connect(node_table_[rank]->sender, ip_port.c_str()))
      << "rank:" << rank << " connect failure, addr:" << node_table_[rank]->addr;
  }

  void ZMQ_NetWork::Send(int rank, msg::MessagePtr& msg) {
    if (!msg) return;
    CHECK(node_table_.count(rank)) << "rank:" << rank << " does not exist.";
    CHECK(node_table_[rank].sender) << "regist rank[" << rank << "] socket first";
    int buf[3];
    buf[0] = (int)msg->type; buf[1] = msg->form; buf[2] = rank;
    const void*& socket = node_table_[rank].sender;
    zmq_send(socket, buf, sizeof(int) * 3, ZMQ_SNDMORE);
    buf[0] = (int)(msg->blob.size());
    zmq_send(socket, buf, sizeof(int), ZMQ_SNDMORE);
    zmq_send(socket, msg->blob.data(), msg->blob.size(), 0);
  }

  void ZMQ_NetWork::Receive(int rank, msg::MessagePtr& msg) {
    if (!msg) msg.reset(new msg::Message);
    CHECK(node_table_.count(rank)) << "rank:" << rank << " does not exist.";
    CHECK(node_table_[rank].receiver) << "regist rank[" << rank << "] socket first";
    const void*& socket = node_table_[rank].receiver;
    int buf[4];
    zmq_recv(socket, buf, sizeof());
  }

}
