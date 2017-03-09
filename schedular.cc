/*
 * schedular.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */


#include <functional>

#include "schedular.h"
#include "./net/communicator.h"


namespace msg {

  virtual void Schedular::Prestart() {
    this->handlers_[msg::REGIST_ACTOR] =
      std::bind(&Schedular::RegistActor, this, std::placeholders::_1);
    this->handlers_[msg::REQUEST_ACTOR_TABLE] =
      std::bind(&Schedular::GetLocationTable, this, std::placeholders::_1);
    this->default_handler_ =
      std::function<void(msg::MessagePtr)>(
          [](msg::messagePtr) -> {});
  }

  virtual void Schedular::PostExit() {
  }

  void Schedular::RegistActor(const msg::MessagePtr& message) {
    message->from.rank = 
    this->locations_.insert(message->from);
    Message* reply = CreateSmartReply(&(*message));
    network::Communicator::Get()->SendTo(reply);
  }

  void Schedular::GetLocationTable(msg::MessagePtr message) {
  }
}
