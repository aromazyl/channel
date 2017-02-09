/*
 * network.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <unordered_map>
#include "../message.h"

namespace net {

enum NetType {
  MPI = 0,
  ZMQ = 1,
  SOCKET = 2,
};

class NetWork {
  public:
    NetWork() {}
    virtual ~NetWork() {}
  private:
    NetWork(const NetWork&) {}
    void operator=(const NetWork&) {}

  public:
    virtual void Init(int* argc, char** argv) = 0;
    virtual void Finalize() = 0;
    virtual void Bind(int rank, const std::string& port) = 0;
    virtual void Connect(int rank, const std::string& port) = 0;
    virtual void Send(int rank, const msg::MessagePtr& msg) = 0;
    virtual void Receive(msg::MessagePtr& msg) = 0;
    virtual int NodeNums() const = 0;
    virtual void RegisterNetNode(int rank, const std::string& name) = 0;
    virtual int MyRank() const = 0;

  protected:
};
}

#endif /* !NETWORK_H */
