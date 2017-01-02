/*
 * memory_pool.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "memory_pool.h"


namespace zyl {
char* Allocator::Alloc(size_t size) {
  if (size < 32) size = 32;
  else {
    size -= 1;
    size |= size >> 32;
    size |= size >> 16;
    size |= size >> 8;
    size |= size >> 4;
    size |= size >> 2;
    size += 1;
  }
  if (!pool_.count(size)) pool_[size] = new BlockList(size);
  return pool_[size]->Pop();
}
}
