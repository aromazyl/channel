/*
 * push_protocol.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PUSH_PROTOCOL_H
#define PUSH_PROTOCOL_H

#include "message.h"
#include "protocol/protocol.h"

namespace protocol {
  using namespace msg;

  // encode keys number, keys ..., values...
  template <>
  struct Encoder<PUSH> {
    template <typename Key, typename Val>
    bool Apply(const Location& from, const Location& to,
        const std::vector<Key>& keys, const std::vector<Val>& vals, Message** msg) {
      if (!(*msg)) *msg = new Message;
      (*msg)->type = PUSH;
      (*msg)->from = from;
      (*msg)->to = to;
      (*msg)->blob.resize(sizeof(Key) * keys.size() + sizeof(Val) * vals.size() + sizeof(int));
      (*msg)->blob.CopyFrom(&keys[0], sizeof(Key) * keys.size());
      return true;
    }
  };

  template <>
  struct Decoder<PUSH> {
    template <typename Key, typename Val>
    bool Apply(const Message& msg, Location* from,
        Location* to, std::vector<Key>* keys, std::vector<Val>* vals) {
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

      if (!vals) {
        LOG(ERROR) << "val is empty. decode failure";
        return false;
      }

      int num = reinterpret_cast<int*>(msg.blob.data())[0];
      keys->resize(num);
      vals->resize(num);
      Key* k = (Key*)((char*)(msg.blob.data()) + sizeof(int));
      Val* v = (Val*)((char*)k + sizeof(Key) * num);

      for (int i = 0; i < num; ++i) {
        keys[i] = k[i]; vals[i] = v[i];
      }
      return true;
    }
  };
}

#endif /* !PULL_PROTOCAL_H */
