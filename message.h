#pragma once

#include <functional>
#include <unordered_map>
#include <queue>
#include <memory>
#include "blob.h"

namespace msg {

enum MsgType {
  STOP_ACK = -3;
  SEND_ACK = -2;
  RCV_ACK = -1;
  DEFAULT = 0;
  RCV  = 1;
  SEND = 2;
  STOP = 3;
};

struct Message {
  MsgType type;
  int from;
  int to;
  Blob blob;
};

typedef std::shared_ptr<Message> MessagePtr;
typedef Function<void(MessagePtr)> MessageHandler;

class Actor {
  public:
    Actor();
    ~Actor() {}

  public:
    virtual void PreStart() = 0;
    virtual void Receive(Message* msg) = 0;
    virtual void PostExit() = 0;

  protected:
    std::unordered_map<MsgType, MessageHandler> handlers_;
    std::queue<Message*> msgbox_;
};
}
