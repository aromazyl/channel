/*
 * sparse_hash_kvstore.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SPARSE_HASH_KVSTORE_H
#define SPARSE_HASH_KVSTORE_H

#include <mutex>
#include <memory>
// #include <sparsehash/sparse_hash_map>
#include <unordered_map>
#include "kvstore_base.h"

namespace kvstore {
  template <typename Key, typename Value>
  class SparseHashKVStore : public KVStoreBase<Key, Value> {
    public:
      const Value& Get(const Key& key) {
        return data_[key];
      }
      void Save(const Key& key, const Value& value) {
        std::unique_lock<std::mutex> lock(mu_);
        data_[key] = value;
      }

    private:
      std::mutex mu_;
      // google::sparse_hash_map<Key, Value> data_;
      std::unordered_map<Key, Value> data_;
  };
}

#endif /* !SPARSE_HASH_KVSTORE_H */
