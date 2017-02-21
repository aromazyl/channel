/*
 * schedular.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SCHEDULAR_H
#define SCHEDULAR_H

#include "./actor.h"
#include "./message.h"

namespace msg {
  class Schedular : public Actor {
    public:
      virtual void PreStart();
      virtual void PostExit();

    private:

  };
}

#endif /* !SCHEDULAR_H */
