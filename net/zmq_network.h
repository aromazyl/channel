/*
 * zmq_network.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ZMQ_NETWORK_H
#define ZMQ_NETWORK_H

#include "./network.h"
#include <zmq.h>
#include <unordered_map>
#include <string>
#include <memory>

namespace net {

struct ZMQ_Entity {
  int remote_rank;
  std::string addr;
  zmq_socket* sender = NULL;
  zmq_socket* receiver = NULL;
};

using ZMQEntityPtr = std::shared_ptr<ZMQ_Entity>;

class ZMQ_NetWork : public NetWork {
  public:
    void Init(int* argc, char** argv);

    void Finalize();

    void Bind(int rank);

    void Connect(int rank);

    void Send(int rank);

    void Receive(int rank, msg::MessagePtr& msg);

    int NodeNums() const;

    void RegisterNetNode(int rank, const std::string& addr);

  private:
    std::unordered_map<int, ZMQEntityPtr> node_table_;
    ZMQ_Entity self_entity_;
};
}

#endif /* !ZMQ_NETWORK_H */
