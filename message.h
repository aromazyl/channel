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
typedef std::function<void(MessagePtr)> MessageHandler;

}
