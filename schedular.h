/*
 * schedular.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SCHEDULAR_H
#define SCHEDULAR_H

#include <unordered_set>

#include "actor.h"
#include "message.h"
#include "location.h"

namespace msg {
  class Schedular : public Actor {
    public:
      virtual void PreStart();
      virtual void PostExit();

    public:
      void SendInfos(const Location& loc);
      void ReceiveNodeInfoHandler(Message* message);

    private:
      void RegistActor(const msg::MessagePtr& message);
      void GetLocationTable(msg::MessagePtr message);
      std::vector<Location> locations_;
      // set::set<int> registed_hosts_;
  };
}

#endif /* !SCHEDULAR_H */
