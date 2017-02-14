// Copyright 2017 zhangyule
//

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <functional>
#include <unordered_map>
#include <queue>
#include <memory>
#include "memory/blob.h"
#include "./base/thread_pool/thread_safe_queue.hpp"
#include <thread>

namespace msg {

enum MsgType {
  CONTINUTE_ACK = -4,
  STOP_ACK = -3,
  PUSH_ACK = -2,
  PULL_ACK = -1,
  DEFAULT = 0,
  PULL = 1,
  PUSH = 2,
  STOP = 3,
  CONTINUTE = 4,
};

struct Message {
  MsgType type;
  int from;
  int to;
  blob::Blob blob;
  Message* CreateReply();
};

Message* Message::CreateReply() {
  auto msg_r = new Message;
  msg_r->type *= -(this->type);
  msg_r->from = this->to;
  msg_r->to = this->from;
  return msg_r;
}

typedef std::shared_ptr<Message> MessagePtr;
typedef std::function<void(Message*)> MessageHandler;

}

#endif
