/*
 * kvstore_actor.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <functional>
#include <glog/logging.h>
#include "./sparse_hash_kvstore.h"
#include "kvstore_actor.h"
#include "../message.h"


namespace kvstore {
  template <typename Key, typename Value, typename Spliter>
  virtual void KVStoreActor<Key, Value, Spliter>::PreStart() {
    using std::placeholders;
    store_ = new SparseHashKVStore();
    // ADD Message handler definition
  }

  template <typename Key, typename Value, typename Spliter>
  virtual void KVStoreActor<Key, Value, Spliter>::Receive(Message* msg) {
    CHECK(msg) << "Message is NULL!";
    const msg::MsgType& type = msg->type;
    switch (type) {
      case msg::STOP: is_running_ = false; break;
      case msg::PULL: pullHandler_(msg); break;
      case msg::PUSH: pushHandler_(msg); break;
      case default: LOG(ERROR) << "Illegal type";
    }
  }
 
  template <typename Key, typename Value, typename Spliter>
  virtual void KVStoreActor<Key, Value, Spliter>::PostExit() {
    delete store_;
  }
}
