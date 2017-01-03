/*
 * memory_pool.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "memory_pool.h"


namespace zyl {
namespace {
  const int kPointerSize = sizeof(void*);
}
char* Allocator::Alloc(size_t size) {
  if (size < 32) size = 32;
  else {
    size -= 1;
    size |= size >> 32;
    size |= size >> 16;
    size |= size >> 8;
    size |= size >> 4;
    size |= size >> 2;
    size |= size >> 1;
    size += 1;
  }
  {
    std::lock_guard<std::mutex> lock(*mutex_); 
    if (!pool_.count(size)) pool_[size] = new BlockList(size);
    auto ret = pool_[size]->Pop();
  }
  return ret;
}

void Allocator::Free(char* data) {
  ((MemoryBlock*)(data - kPointerSize))->UnLink();
}

void Allocator::Ref(char* data) {
  ((MemoryBlock*)(data - kPointerSize))->Link();
}

Allocator::Allocator() {
  mutex_ = new std::mutex;
}

BlockList::BlockList(size_t size) {
  free_ = nullptr;
  size_ = size;
}

BlockList::~BlockList() {
  while (free_ != nullptr) {
    auto del = free_;
    free_ = free_->next;
    delete del;
  }
}

char* BlockList::Pop() {
  if (free_ == nullptr) {
    free_ = new MemoryBlock(size_, this);
  }
  auto ret = free_->data();
  free_ = free_->next;
  return ret;
}

void BlockList::Push(MemoryBlock* data) {
  data->next = free_;
  free_ = data;
}

MemoryBlock::MemoryBlock(size_t size, BlockList* list) {
  data_ = (char*)malloc(size + kPointerSize);
  list_ = list;
  *(void**)data_ = (void*)this;
}

MemoryBlock::~MemoryBlock() {
  free(data_);
  data_ = nullptr;
}

char* MemoryBlock::data() {
  return data_ + kPointerSize;
}

void MemoryBlock::Link() {
  ref_ += 1;
}

void MemoryBlock::UnLink() {
  ref_ -= 1;
  if (ref_ == 0) {
    free_->Push(this);
  }
}

}
