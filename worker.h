/*
 * worker.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef WORKER_H
#define WORKER_H

#include "./actor.h"

namespace customer {
  class Worker : public Actor {
    public:
      void PreStart();
      void PostExit();
    // todo concrete algorithm
  };
}

#endif /* !WORKER_H */
