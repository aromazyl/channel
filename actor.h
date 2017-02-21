/*
 * actor.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ACTOR_H // NOLINT
#define ACTOR_H // NOLINT

#include <unordered_map>
#include <condition_variable>
#include <functional>

#include "base/string_printf.hpp"
#include "./message.h"
#include "./location.h"

namespace msg {
class Actor {
 public:
   Actor() {}
   ~Actor() {}

 public:
   virtual void PreStart() = 0;

   virtual void PostExit() = 0;

   virtual void Barrier(std::function<bool()>* condition);

 public:
   void Receive(MessagePtr msg) { this->msgbox_.Push(msg); }

   virtual void Run() {
     PreStart();
     is_running_ = true;
     while (is_running_) {
       MessagePtr tmp_msg;
       if (msgbox_.TryPop(tmp_msg)) {
         if (handlers_.count(tmp_msg->type)) {
           handlers[tmp_msg->type](tmp_msg);
         } else {
           CHECK(default_handler_) <<
             base::StringPrintf(
                 "default handler is empty, "
                 "cannot handler msginfo : type:%d, from:%d, to:%d\n",
                 tmp_msg->type, tmp_msg->from, tmp_msg->to);
           default_handler_(tmp_msg);
         }
       } else {
         std::this_thread::yield();
       }
     }
     PostExit();
   }

 public:
   // global identity
   Location id;

 protected:
   std::unordered_map<MsgType, MessageHandler> handlers_;
   msg::MessageHandler default_handler_;
   ThreadSafeQueue<MessagePtr> msgbox_;
   std::atomic<bool> is_running_;
   std::mutex mu_;
   std::condition_variable cond_;
};
} // namespace msg


#endif /* !ACTOR_H */ // NOLINT
