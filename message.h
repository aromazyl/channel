// Copyright 2017 zhangyule
//

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <functional>
#include <unordered_map>
#include <queue>
#include <memory>
#include <thread>
#include <string>
#include <glog/logging.h>

#include "base/string_printf.hpp"
#include "memory/blob.h"
#include "memory/memory_pool.h"
#include "base/thread_pool/thread_safe_queue.hpp"
#include "location.h"

namespace msg {

struct Message;
typedef std::shared_ptr<Message> MessagePtr;
typedef std::function<void(Message*)> MessageHandler;

enum MsgType {
  BCAST_TABLE_REPLY = -9,
  HEART_BEAT_ACK = -8,
  SHUTDOWN_ACK = -7,
  REQUEST_ACTOR_TABLE_ACK = -6,
  REGIST_ACTOR_ACK = -5,
  CONTINUTE_ACK = -4,
  STOP_ACK = -3,
  PUSH_ACK = -2,
  PULL_ACK = -1,
  DEFAULT = 0,
  PULL = 1,
  PUSH = 2,
  STOP = 3,
  CONTINUTE = 4,
  REGIST_ACTOR = 5,
  REQUEST_ACTOR_TABLE = 6,
  SHUTDOWN = 7,
  HEART_BEAT = 8,
  BCAST_TABLE = 9,
};

struct Message {
  MsgType type;
  Location from;
  Location to;
  blob::Blob blob;
};

inline
std::string DumpMessageInfo(const Message& msg_info) {
  return base::StringPrintf("msg type:%d, from:%s, to:%s, blob:%s",
      msg_info.type,
      DumpLocationInfo(msg_info.from).c_str(),
      DumpLocationInfo(msg_info.to).c_str(),
      DumpBlobInfo(msg_info.blob).c_str());
}

inline
Message* CreateReply(Message* message) {
  auto msg_r = new Message;
  msg_r->type = MsgType(-(message->type));
  msg_r->from = message->to;
  msg_r->to = message->from;
  return msg_r;
}

inline
MessagePtr CreateSmartReply(Message* message) {
  MessagePtr msg_ptr = std::make_shared<Message>();
  msg_ptr->type = MsgType(-(message->type));
  msg_ptr->from = message->to;
  msg_ptr->to = message->from;
  return msg_ptr;
}

inline
void SerializeMessage(Message* message, void** buf, int* size) {
  CHECK(*buf == NULL) << base::StringPrintf("buf is not empty, address:%p", *buf);
  CHECK(message) << base::StringPrintf("message pointer is empty.");
  *size = sizeof(msg::MsgType) + 2 * sizeof(Location) + message->blob.size() + sizeof(size_t);
  *buf = mem::Allocator::Get()->Alloc(*size);
  char* ptr = static_cast<char*>(*buf);
  memcpy(&(message->type), ptr, sizeof(msg::MsgType) +
      sizeof(Location) * 2);
  ptr += sizeof(msg::MsgType) + sizeof(Location) * 2;
  *ptr = message->blob.size();
  ptr += sizeof(size_t);
  memcpy(ptr, message->blob.data(), message->blob.size());
}

inline
void DeserializeMessage(Message* message, void* buf, int size) {
  CHECK(message) << base::StringPrintf("message is empty");
  const int kCopySize = sizeof(msg::MsgType) + 2 * sizeof(Location);
  memcpy(&(message->type), buf, kCopySize);
  char* p = (char*)buf;
  p += kCopySize;
  size_t blobsize = *(size_t*)p;
  message->blob.resize(blobsize);
  p += sizeof(size_t);
  message->blob.CopyFrom(p, blobsize);
}


}

#endif
