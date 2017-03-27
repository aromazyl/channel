/*
 * pull_protocal.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PULL_PROTOCAL_H
#define PULL_PROTOCAL_H

#include "message.h"
#include "protocol/protocol.h"

namespace protocol {
  using namespace msg;

  template <>
  struct Encoder<PULL> {
    template <typename Key>
    bool Apply(const Location& from, const Location& to, const std::vector<Key>& keys, Message** msg) {
      if (!(*msg)) *msg = new Message;
      (*msg)->type = PULL;
      (*msg)->from = from;
      (*msg)->to = to;
      (*msg)->blob.resize(sizeof(Key) * keys.size());
      (*msg)->blob.CopyFrom(&keys[0], sizeof(Key) * keys.size());
      return true;
    }
  };

  template <>
  struct Decoder<PULL> {
    template <typename Key>
    bool Apply(const Message& msg, Location* from, Location* to, std::vector<Key>* keys) {
      if (!from || !to) {
        LOG(ERROR) << "from or to is empty. decode failure.";
        return false;
      }

      *from = msg.from;
      *to = msg.to;
      if (!keys) {
        LOG(ERROR) << "key is empty. decode failure.";
        return false;
      }

      if (msg.blob.size() % sizeof(Key) != 0) {
        LOG(ERROR) << base::StringPrintf("Informal key size:%d and blob size: %d\n",
            msg.blob.size(), sizeof(Key));
        return false;
      }

      keys->resize(msg.blob.size() / sizeof(Key));

      for (int i = 0; i < msg.blob.size() / sizeof(Key); ++i) {
        keys[i] = (int*)(msg.blob.data())[i];
      }

      return true;
    }
  };
}

#endif /* !PULL_PROTOCAL_H */
