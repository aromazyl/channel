/*
 * kvstore_actor.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef KVSTORE_ACTOR_H
#define KVSTORE_ACTOR_H

#include <unordered_map>
#include <mutex>
#include "./kvstore_base.h"
#include "sparse_hash_kvstore.h"
#include "../message.h"

namespace kvstore {
  template <typename Key, typename Value, typename Spliter>
  class KVStoreActor : public msg::Actor {
    public:
      KVStoreActor() {};
      virtual ~KVStoreActor() {};

    public:
      virtual void PreStart();
      virtual void Receive(Message* msg);
      virtual void PostExit();

    private:
      void Pull(const std::vector<Key>& keys, msg::Message* values);

      void Push(const std::vector<Key>& keys,
          const std::vector<Value>& values);

    private:
      msg::MessageHandler pullHandler_;
      msg::MessageHandler pushHandler_;
      std::mutex lock_;

    private:
      KVStoreBase* store_;
  };

  template <typename Key, typename Value, typename Spliter>
  void KVStoreActor::PreStart() {
     store_ = new SparseHashKVStore();
     pullHandler_ = std::make_shared<>();
  }
}


#endif /* !KVSTORE_ACTOR_H */