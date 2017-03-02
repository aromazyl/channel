/*
 * blob.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <string.h>
#include <glog/logging.h>

#include "blob.h"
#include "../base/string_printf.hpp"


namespace blob {

Blob::Blob() : memory_(NULL), size_(0) {}

Blob::Blob(size_t size) {
  memory_ = NULL;
  size_ = 0;
  this->resize(size);
}

Blob::~Blob() {
  if (memory_) {
    mem::Allocator::Get()->Free(memory_);
  }
  size_ = 0;
}

Blob::Blob(const Blob& blob) {
  this->memory_ = mem::Allocator::Get()->Refer(blob.memory_);
  this->size_ = blob.size_;
}

Blob& Blob::operator=(const Blob& blob) {
  this->CopyFrom(blob.data(), blob.size());
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

size_t Blob::size() const { return size_; }

void Blob::resize(size_t size) {
  if (size == 0) return;
  if (memory_ != NULL) {
    mem::Allocator::Get()->Free(memory_);
  }
  memory_ = mem::Allocator::Get()->Alloc(size);
  size_ = size;
}

std::string DumpBlobInfo(const Blob& blob) {
  return base::StringPrintf("blob size:%d, blob info:%s",
      blob.size(), blob.data());
}

}
