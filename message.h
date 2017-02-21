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
  REQUEST_ACTOR_TABLE_ACK = -6,
  REGISTER_ACTOR_ACK = -5,
  CONTINUTE_ACK = -4,
  STOP_ACK = -3,
  PUSH_ACK = -2,
  PULL_ACK = -1,
  DEFAULT = 0,
  PULL = 1,
  PUSH = 2,
  STOP = 3,
  CONTINUTE = 4,
  REGISTER_ACTOR = 5,
  REQUEST_ACTOR_TABLE = 6,
};

struct Message {
  MsgType type;
  Location from;
  Location to;
  blob::Blob blob;
};

inline
Message* CreateReply(Message* message) {
  auto msg_r = new Message;
  msg_r->type = -(this->type);
  msg_r->from = this->to;
  msg_r->to = this->from;
  return msg_r;
}

inline
void SerializeMessage(Message* message, void** buf, int* size) {
}

inline
void DeserializeMessage(Message* message, void* buf, int size) {
}

typedef std::shared_ptr<Message> MessagePtr;
typedef std::function<void(Message*)> MessageHandler;

}

#endif
