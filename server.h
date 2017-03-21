/*
 * server.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SERVER_H
#define SERVER_H

#include "./actor.h"
#include "./kvstore/kvstore_actor.h"

namespace customer {
  class Server : public Actor {
    public:
    private:
      kvstore::KVStoreActor<uint64_t, double> kvstore_;
  };
}

#endif /* !SERVER_H */
