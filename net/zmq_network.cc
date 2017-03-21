/*
 * zmq_network.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <glog/logging.h>
#include <assert.h>
#include <errno.h>
#include <zmq.h>

#include "zmq_network.h"
#include "base/string_printf.hpp"


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
    zmq_term(context_);
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
    void* buf = NULL;
    int size = 0;

    /*
    buf[0] = (int)msg->type; buf[1] = msg->from; buf[2] = msg->to; buf[3] = msg->blob.size();
    */
    SerializeMessage(&(*msg), &buf, &size);

    void* socket = node_table_[rank]->sender;
    int ret = zmq_send(socket, buf, size, 0);
    // int ret = zmq_send(socket, s_message, ZMQ_SNDMORE);
    // ret = zmq_send(socket, msg->blob.data(), msg->blob.size(), 0);
    // ret = zmq_send(socket, s_message, 0);

    CHECK(ret != -1) <<
      base::StringPrintf("blob:%s, size:%u, send failure\n",
        msg->blob.data(), msg->blob.size());
  }

  void ZMQ_NetWork::Receive(msg::MessagePtr& msg) {

    if (!msg) msg.reset(new msg::Message);

    void* socket = self_entity_.receiver;
    // TODO {receive message}

    /*

    if ((int)msg->blob.size() != buf[3])
      msg->blob.resize(buf[3]);

    // int recv_size = zmq_recv(socket, buf, 4 * sizeof(int), 0);

    msg->blob.resize(buf[3]);
    recv_size = zmq_recv(socket, msg->blob.data(), buf[3], 0);

    msg->type = msg::MsgType(buf[0]);
    msg->from = buf[1];
    msg->to   = buf[2];

    */

    // zmq_recv(socket, buf, sizeof(buf), 0);
    zmq_msg_t rmsg;
    int rc = zmq_msg_init(&rmsg);
    assert(rc == 0);
    rc = zmq_recvmsg(socket, &rmsg, 0);
    assert(rc == 0);
    zmq_msg_close(&rmsg);
    size_t msg_size = zmq_msg_size(&rmsg);
    char* buf = mem::Allocator::Get()->Alloc(zmq_msg_size(&rmsg));

    DeserializeMessage(&(*msg), buf, msg_size);
    mem::Allocator::Get()->Free(buf);
    /*
    CHECK(recv_size != -1) <<
      base::StringPrintf("socket:%p,"
          "receive blob data failure, data size:%d\n",
        socket, sizeof(buf));
     */
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

  int ZMQ_NetWork::MyRank() const {
    return self_entity_.rank;
  }
}
