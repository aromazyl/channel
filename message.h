#pragma once

#include <functional>
#include <unordered_map>
#include <queue>
#include <memory>
#include "memory/blob.h"
#include "./base/thread_pool/thread_safe_queue.hpp"
#include <thread>

namespace msg {

enum MsgType {
  STOP_ACK = -3,
  PUSH_ACK = -2,
  PULL_ACK = -1,
  DEFAULT = 0,
  PULL = 1,
  PUSH = 2,
  STOP = 3,
};

struct Message {
  MsgType type;
  int from;
  int to;
  blob::Blob blob;
};

typedef std::shared_ptr<Message> MessagePtr;
typedef std::function<void(Message*)> MessageHandler;

class Actor {
  public:
    Actor();
    ~Actor() {}

  public:
    virtual void PreStart() = 0;
    virtual void Receive(Message* msg) = 0;
    virtual void PostExit() = 0;

    virtual void Run() {
      PreStart();
      is_running_ = true;
      while (is_running_) {
        Message* tmp_msg;
        if (msgbox_.TryPop(tmp_msg)) {
          Receive(tmp_msg);
        } else {
          std::this_thread::yield();
        }
      }
      PostExit();
    }

  protected:
    std::unordered_map<MsgType, MessageHandler> handlers_;
    ThreadSafeQueue<Message*> msgbox_;
    std::atomic<bool> is_running_;
    std::mutex mu_;
};
}
