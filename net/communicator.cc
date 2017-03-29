/*
 * communicator.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "communicator.h"

#include <stdio.h>
#include "../kvstore/kvstore_actor.h"
#include "./zmq_network.h"
#include "../conf/configure.h"

// TODO 规划 id 分配
namespace net {
  void Communicator::PreStart() {
    // create communicator
    net_ = new ZMQ_NetWork;
    net_->Init(NULL, NULL);

    CHECK(Configure::Get()->IsExistConf("SCHEDULAR"));
    FILE* fs = fopen(Configure::Get()->GetConf("SCHEDULAR").c_str(), "r");
    char ip[20];
    int host;
    fscanf(fs, "%s:%d", ip, &host);
    fclose(fs);
  }

  void Communicator::PostExit() {
    is_running_ = false;
  }

  void Communicator::Register(Actor* actor) {
    local_actors_[actor->id] = actor;
  }

  void Communicator::SendTo(msg::MessagePtr mmsg) {
    if (local_actors_.count(mmsg->to)) {
      local_actors_[mmsg->to]->Receive(mmsg);
    } else {
      const int& remote_rank = mmsg->to.rank;
      net_->Send(remote_rank, mmsg);
    }
  }
}
