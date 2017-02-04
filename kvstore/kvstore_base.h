/*
 * kvstore_base.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef KVSTORE_BASE_H
#define KVSTORE_BASE_H

namespace kvstore {
  template <typename Key, typename Value>
  class KVStoreBase {
    public:
      const Value& Get(const Key& ) = 0;
      void Save(const Key&, const Value&) = 0;
  };
}

#endif /* !KVSTORE_BASE_H */
