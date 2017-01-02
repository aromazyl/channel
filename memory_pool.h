/*
 * memory_pool.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <atomic>

namespace zyl {

const int kPointerSize = sizeof(void*);

class Allocator;
class MemoryBlock;
class BlockList;

class Allocator {
  public:
    char* Alloc(size_t size);
    void Free(char*);
    void Refer(char*);
    static Allocator* Get() {
      static Allocator allocator;
      return &allocator;
    }

  private:
    Allocator();
    Allocator(const Allocator&);
    Allocator& operator=(const Allocator&);

  private:
    std::unordered_map<size_t, BlockList*> pool_;
    std::mutex* mutex_;
};

class BlockList {
  public:
    BlockList(size_t size);
    ~BlockList();
    char* Pop();
    void Push(MemoryBlock*);
  private:
    size_t size_;
    MemoryBlock* free_;
};

class MemoryBlock {
  public:
    MemoryBlock(size_t size, BlockList* list);
    ~MemoryBlock();
  public:
    char* data();
    char* Ref();
    void Link();
    void UnLink();
  public:
    MemoryBlock* next;

  private:
    char* data_;
    std::atomic<int> ref_ = 1;
};

}

#endif /* !MEMORY_POOL_H */
