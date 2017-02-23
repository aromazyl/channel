/*
 * schedular.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SCHEDULAR_H
#define SCHEDULAR_H

#include <set>

#include "./actor.h"
#include "./message.h"
#include "./location.h"

namespace msg {
  class Schedular : public Actor {
    public:
      virtual void PreStart();
      virtual void PostExit();

    private:
      void RegistActor(const msg::MessagePtr& message);
      void GetLocationTable(msg::MessagePtr message);
      std::set<Location> locations_;
      set::set<int> registed_hosts_;
  };
}

#endif /* !SCHEDULAR_H */
