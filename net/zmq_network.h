/*
 * zmq_network.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ZMQ_NETWORK_H
#define ZMQ_NETWORK_H

#include "./network.h"

namespace net {
class ZMQ_NetWork : public NetWork {
  public:
    void Init(int* argc, char** argv);
    void Finalize();
    void Bind(int rank);
    void Connect(int rank);
    void Send(int rank);
    void Receive(int rank, msg::MessagePtr& msg);
    int NodeNums() const;
    void RegisterNetNode(int rank, const std::string& name);
  private:
    std::unordered_map<int, std::string> node_table_;
};
}

#endif /* !ZMQ_NETWORK_H */
