/*
 * fast_io.cc
 * Copyright (C) 2016 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "fast_io.h"
#include <glog/logging.h>


LineStream::LineStream() {
  fd_ = NULL;
  buf_ = NULL;
  chunk_capacity_ = 0;
  max_cache_size_ = 0;
  cache_size_ = 0;
  offset_ = 0;
  pos_ = 0;
}
LineStream::~LineStream() {
  Destory();
}
void LineStream::Init(int buf_size, int chunk_capacity) {
  buf_ = (char*)malloc(buf_size);
  if (0 == buf_) {
    fprintf(stderr, "memory size:%d malloc failure\n", buf_size);
    exit(1);
  }
  data_chunk_.reserve(chunk_capacity);
  max_cache_size_ = buf_size;
}

void LineStream::Destory() {
  if (buf_) { free(buf_); buf_ = 0; }
}

bool LineStream::GetLine(char** s, int* len) {
  if (pos_ >= cache_size_) {
    bool ret = Read();
    if (ret == false) return false;
  }
  uint64_t i = pos_;
  for (; buf_[i] != '\0' && buf_[i] != '\n'; ++i);
  *s = buf_ + pos_;
  *len = i - pos_ + 1;
  pos_ = i + 1;
  return true;
}

bool LineStream::Read() {
  LOG(INFO) << "reading";
  pos_ = 0;
  if (offset_ > 0) {
    LOG(INFO) << "offset: " << offset_;
    memcpy(buf_, &data_chunk_[0], sizeof(char) * offset_);
  }
  int readed = fread(buf_ + offset_, sizeof(char), max_cache_size_ - offset_, fd_);
  LOG(INFO) << "fread done";
  if (readed == 0) {
    if (ferror(fd_)) { fprintf(stderr, "ferror:%d, read failure", ferror(fd_)); exit(1); }
    fprintf(stderr, "read endl");
    return false;
  }
  if (readed < max_cache_size_ - offset_) {
    offset_ = 0;
    cache_size_ = readed;
  } else {
    offset_ = 0;
    while (buf_[max_cache_size_ - offset_ - 1] != '\n') {
      ++offset_;
    }
    if (offset_ != 0) {
      if (offset_ > chunk_capacity_) {
        data_chunk_.reserve(offset_ * 2);
        chunk_capacity_ = offset_ * 2;
      }
      memcpy(&data_chunk_[0], buf_ + max_cache_size_ - offset_, sizeof(char) * offset_);
    }
    cache_size_ = max_cache_size_ - offset_;
  }
#ifdef DEBUG
  LOG(INFO) << this->DumpInfo();
#endif
  return true;
}
