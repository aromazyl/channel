#pragma once

#include <functional>
namespace msg {
enum MSG {
  RCV  = 1;
  SEND = 2;
  STOP = 3;
  ACK  = 4;
};

class Message {
};

typedef Function<void()>
class Actor {
  public:
  private:

};
}
