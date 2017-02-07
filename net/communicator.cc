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
namespace network {
  void Communicator::PreStart() {
    // create communicator
    net_ = new ZMQ_NetWork;
    net_->Init(NULL, NULL);

    CHECK(Configure::Get()->IsExistConf("NETWORK_TABLE"));
    char ip_port[40];
    int actor_id;
    int net_id;
    char type[10];
    FILE* fs = fopen(Configure::Get()->GetConf("NETWORK_TABLE"), "r");
    while (fscanf(fs, "%s:%d:%d:%s\n", type, actor_id, net_id, ip_port)) {
      net_->RegisterNetNode(net_id, ip_port);
      if (std::string(type) == "local") {
        if (!binded_) net_->Bind(net_id);
      }

      if (std::string(type) == "remote") {
        net_->Connect(net_id);
        remote_[actor_id] = net_id;
      }
    }
    fclose(fs);
  }

  void Communicator::PostExit() {
    running = false;
  }

  void Communicator::Register(Actor* actor) {
    local_actors_[actor->id] = actor;
  }

  void Communicator::SendTo(msg::Message* mmsg) {
    if (local_actors_.count(mmsg->to)) {
      local_actors_[mmsg->to]->Receive(mmsg);
    } else {
      const int& remote_rank = remote_[mmsg->to];
      msg::MessagePtr msg_ptr(new msg::Message);
      msg_ptr->type = mmsg->type;
      msg_ptr->from = mmsg->from;
      msg_ptr->to = mmsg->to;
      msg_ptr->blob.resize(mmsg->blob.size());
      msg_ptr->blob = mmsg->blob;
      net_->Send(remote_rank, msg_ptr);
    }
  }
}
