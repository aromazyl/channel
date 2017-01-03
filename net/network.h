/*
 * network.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef NETWORK_H
#define NETWORK_H

#include "../message.h"

namespace net {
class NetWork {
  private:
    NetWork() {}
    ~NetWork() {}
    NetWork(const NetWork&) {}
    void operator=(const NetWork&) {}

  public:
    static NetWork* Get();
    virtual void Init(int* argc, char** argv) = 0;
    virtual void Finalize() = 0;


  protected:
};
}

#endif /* !NETWORK_H */
