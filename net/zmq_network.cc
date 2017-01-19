/*
 * zmq_network.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "zmq_network.h"
#include "../base/string_printf.hpp"
#include <glog/logging.h>
#include <errno.h>


namespace net {
  void ZMQ_NetWork::Init(int* argc, char** argv) {
    context_ = zmq_ctx_new();
    zmq_ctx_set(context_, ZMQ_MAX_SOCKETS, 256);
  }

  void ZMQ_NetWork::Finalize() {
    for (auto iter = node_table_.begin();
        iter != node_table_.end(); ++iter) {
      if (iter->second->sender) {
        zmq_close(iter->second->sender);
        iter->second->sender = NULL;
      }
      if (iter->second->receiver) {
        zmq_close(iter->second->receiver);
        iter->second->receiver = NULL;
      }
    }
    zmq_ctx_destroy(context_);
  }

  void ZMQ_NetWork::Bind(int rank, const std::string& port) {
    CHECK(context_) << "Init ZMQ context firstly!";
    CHECK(this->node_table_.count(rank)) << "rank:" << rank
      << " does not registed";
    if (node_table_[rank]->receiver) return;
    node_table_[rank]->receiver = zmq_socket(context_, ZMQ_DEALER);
    int ret;
    CHECK(!(ret = zmq_bind(node_table_[rank]->receiver, (node_table_[rank]->addr + ":" + port).c_str())))
      << base::StringPrintf("ret:%d, rank:%d, addr:%s, port:%s\n",
          ret, rank, node_table_[rank]->addr.c_str(), port.c_str());
    self_entity_.rank = rank;
    self_entity_.addr = node_table_[rank]->addr;
    self_entity_.receiver = node_table_[rank]->receiver;
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

  void ZMQ_NetWork::Send(int rank, const msg::MessagePtr& msg) {
    if (!msg) return;
    CHECK(node_table_.count(rank)) << "rank:" << rank << " does not exist.";
    CHECK(node_table_[rank]->sender) << "regist rank[" << rank << "] socket first";
    int buf[4];
    buf[0] = (int)msg->type; buf[1] = msg->from; buf[2] = rank; buf[3] = msg->blob.size();

    void* socket = node_table_[rank]->sender;
    int ret = zmq_send(socket, buf, sizeof(int) * 4, ZMQ_SNDMORE);
    CHECK(ret != -1) <<
      base::StringPrintf("header: buf[0]=%d,buf[1]=%d,buf[2]=%d,buf[3]=%d,send failure\n",
        buf[0], buf[1], buf[2], buf[3]);

    ret = zmq_send(socket, msg->blob.data(), msg->blob.size(), 0);

    CHECK(ret != -1) <<
      base::StringPrintf("blob:%s, size:%u, send failure\n",
        msg->blob.data(), msg->blob.size());
  }

  void ZMQ_NetWork::Receive(msg::MessagePtr& msg) {
    if (!msg) msg.reset(new msg::Message);
    void* socket = self_entity_.receiver;
    int buf[4] = {0};
    msg->blob.resize(buf[3]);
    int recv_size = zmq_recv(socket, buf, 4 * sizeof(int), 0);
    // int recv_size = zmq_recv(socket, buf, 4 * sizeof(int), ZMQ_DONTWAIT);
    CHECK(recv_size >= 0) << "zmq receive header failure, socket:" << socket
      << ", recv_size:" << recv_size
      << ", errno:" << errno
      << base::StringPrintf("buf:%d,%d,%d,%d", buf[0], buf[1], buf[2], buf[3]);
    blob::Blob blob(buf[3]);
    recv_size = zmq_recv(socket, blob.data(), buf[3], 0);
    CHECK(recv_size != -1) << base::StringPrintf("socket:%p, receive blob data failure, data size:%d\n",
        socket, buf[3]);
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
