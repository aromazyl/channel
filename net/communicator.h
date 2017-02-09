/*
 * communicator.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <functional>
#include "../conf/configure.h"
#include "../message.h"
#include "../actor.h"
#include "./network.h"

namespace network {
class Communicator : public msg::Actor {
  private:
    Communicator();
    Communicator(const Communicator&);
    void operator=(const Communicator&);
  public:
    static Communicator* Get() {
      static Communicator comm;
      return &comm;
    }

  public:
    void PreStart();
    void PostExit();

    void Register(Actor* actor);
    void SendTo(msg::MessagePtr msg);

  private:
    // actors: id to actor
    std::unordered_map<int, Actor*> local_actors_;
    // actor id to machine id
    std::unordered_map<int, int> remote_;
    NetWork* net_;
    bool binded_ = false;
};
}

#endif /* !COMMUNICATOR_H */
