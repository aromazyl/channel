/*
 * zmq_network.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "zmq_network.h"
#include "../base/string_printf.hpp"
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
    int buf[4];
    buf[0] = (int)msg->type; buf[1] = msg->form; buf[2] = rank; buf[4] = msg->blob.size();
    const void*& socket = node_table_[rank].sender;
    zmq_send(socket, buf, sizeof(int) * 4, ZMQ_SNDMORE);
    zmq_send(socket, msg->blob.data(), msg->blob.size(), 0);
  }

  void ZMQ_NetWork::Receive(int rank, msg::MessagePtr& msg) {
    if (!msg) msg.reset(new msg::Message);
    CHECK(node_table_.count(rank)) << "rank:" << rank << " does not exist.";
    CHECK(node_table_[rank].receiver) << "regist rank[" << rank << "] socket first";
    const void*& socket = node_table_[rank].receiver;
    int buf[4];
    msg->blob.resize(buf[3]);
    int recv_size = zmq_recv(socket, buf, 4 * sizeof(int), ZMQ_DONTWAIT);
    CHECK(recv_size != -1) << "zmq receive header failure, socket:\n" << socket;
    blob::Blob blob(buf[3]);
    recve_size = zmq_recv(socket, blob.data(), buf[3], 0);
  }

  int ZMQ_NetWork::NodeNums() const {
    return node_table_.size();
  }

  void ZMQ_NetWork::RegisterNetNode(int rank, const std::string& addr) {
    if (node_table_.count(rank)) {
      LOG(ERROR) << base::StringPrintf("rank:%d, exist in node_table\n", rank);
      return;
    }
    node_table_[rank].reset(new ZMQ_Entity);
    node_table_[rank]->rank = rank;
    node_table_[rank]->addr = addr;
    node_table_[rank]->sender = NULL;
    node_table_[rank]->receiver = NULL;
  }
}
