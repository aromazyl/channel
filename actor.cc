/*
 * actor.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "actor.h"

#include <memory>

namespace msg {
  virtual void Actor::Barrier(std::function<bool()>* condition) {
    std::unique_lock<std::mutex> lock(mu_);
    cond_.wait(lock, *condition);
  }
}
