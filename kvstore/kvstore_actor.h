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
#include "../net/communicator.h"
#include "./kvstore_base.h"
#include "sparse_hash_kvstore.h"
#include "../message.h"
#include "../actor.h"

namespace kvstore {
  template <typename Key, typename Value>
  class KVStoreActor : public msg::Actor {
    public:
      KVStoreActor(int id) { this->id = id; }
      virtual ~KVStoreActor() {}

    public:
      virtual void PreStart();
      virtual void Receive(msg::MessagePtr msg);
      virtual void PostExit();

    private:
      void Pull(const std::vector<Key>& keys, msg::MessagePtr& values);

      void Push(const std::vector<Key>& keys,
          const std::vector<Value>& values);

    private:
      msg::MessageHandler pullHandler_;
      msg::MessageHandler pushHandler_;
      std::mutex lock_;

    private:
      KVStoreBase<Key, Value>* store_;
  };

  template <typename Key, typename Value>
    void KVStoreActor<Key, Value>::PreStart() {
      net::Communicator::Get()->Register(this);
      store_ = new SparseHashKVStore<Key, Value>();
    }

  template <typename Key, typename Value>
    void KVStoreActor<Key, Value>::PostExit() {
      delete store_;
    }

  template <typename Key, typename Value>
    void KVStoreActor<Key, Value>::Pull(
        const std::vector<Key>& keys, msg::MessagePtr& values) {
      values->blob.resize(sizeof(Value) * keys.size() + sizeof(int));
      values->blob.data()[0] = keys.size();
      Value* p = values->blob.data() + sizeof(int);
      for (auto& k : keys) {
        *p = this->store_->Get(k);
        p += sizeof(Value);
      }
    }

  template <typename Key, typename Value>
    void KVStoreActor<Key, Value>::Push(
        const std::vector<Key>& keys, const std::vector<Value>& values) {
      for (size_t i = 0; i < keys.size(); ++i) {
        this->store_->Save(keys[i], values[i]);
      }
    }

}


#endif /* !KVSTORE_ACTOR_H */
