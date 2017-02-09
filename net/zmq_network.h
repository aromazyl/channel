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

class ZMQ_NetWork;

struct ZMQ_Entity {
  int rank;
  std::string addr;
  void* sender = NULL;
  void* receiver = NULL;
};

using ZMQEntityPtr = std::shared_ptr<ZMQ_Entity>;

class ZMQ_NetWork : public NetWork {
  public:
    virtual ~ZMQ_NetWork() {}
  public:
    void Init(int* argc, char** argv);

    void Finalize();

    // set rank receiver
    void Bind(int rank, const std::string& port);

    // set rank sender
    void Connect(int rank, const std::string& port);

    // send message to rank
    void Send(int rank, const msg::MessagePtr& msg);

    // receive message from rank
    void Receive(msg::MessagePtr& msg);

    int NodeNums() const;

    void RegisterNetNode(int rank, const std::string& addr);

    int MyRank() const;

  private:
    std::unordered_map<int, ZMQEntityPtr> node_table_;

    ZMQ_Entity self_entity_;

    void* context_ = NULL;
};
}

#endif /* !ZMQ_NETWORK_H */
