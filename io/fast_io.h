/*
 * fast_io.h
 * Copyright (C) 2016 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef FAST_IO_H
#define FAST_IO_H
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <glog/logging.h>
#ifdef DEBUG
#include <sstream>
#endif

class LineStream {
  public:
    LineStream();
    ~LineStream();

  public:
    void Init(int buf_size, int chunk_capacity_);
    void Destory();
  public:
    bool GetLine(char** s, int* len);
    bool Load(const std::string& filename) {
      if (fd_ != NULL) { fclose(fd_); fd_ = NULL; }
      fd_ = fopen(filename.c_str(), "r");
      CHECK(fd_) << filename << ", open failure";
      return fd_;
    }
#ifdef DEBUG
    std::string DumpInfo() {
      std::ostringstream os;
      os << "file describer:" << fd_
         << ", buffer:" << buf_
         << ", chunk capacity:" << chunk_capacity_
         << ", max_cache_size:" << max_cache_size_
         << ", cache_size_:" << cache_size_
         << ", offset_:" << offset_
         << ", pos_:" << pos_;
      return os.str();
    }
#endif

  private:
    bool Read();

  private:
    FILE* fd_;
    // buf for cache all readed data
    char* buf_;
    // max cache size
    int max_cache_size_;
    // 真实 cache size
    int cache_size_;
    // cache the tail data
    std::vector<char> data_chunk_;
    // max tail data size for cache
    int chunk_capacity_;
    // the tail data len
    int offset_;
    // data used offset
    uint64_t pos_;
};

#endif /* !FAST_IO_H */
