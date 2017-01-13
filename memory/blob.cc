/*
 * blob.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <string.h>
#include <glog/logging.h>

#include "blob.h"


namespace blob {
explicit Blob::Blob(size_t size) {
  this->resize(size);
}

Blob::~Blob() {
  this->memory_ = mem::Allocator::Get()->Free(memory_);
  size_ = 0;
}

explicit Blob::Blob(const Blob& blob) {
  mem::Allocator::Get()->Ref(blob.memory_);
  this->memory_ = blob.memory_;
  this->size = blob.size_;
}

Blob& operator=(const Blob& blob) {
  this->CopyFrom(blob.memory_, blob.size_);
  return *this;
}

int Blob::CopyFrom(char* mem, size_t len) {
  CHECK(len <= this->size_) << "mem size " << len
   << " larger than this blob size: " << this->size_;
  memcpy(this->memory_, mem, len);
  return len;
}

int Blob::CopyTo(char* mem, size_t len) const {
  CHECK(len >= this->size_) << "mem size " << len
   << " less than this blob size: " << this->size_;
  memcpy(mem, this->memory_, size_);
  return this->size_;
}

char* Blob::data() const { return memory_; }

size_t size() const { return size_; }

}
