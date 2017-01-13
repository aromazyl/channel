/*
 * blob.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BLOB_H
#define BLOB_H

#include <memory>
#include "memory_pool.h"

namespace blob {
class Blob {
  public:
    Blob(size_t size);
    ~Blob();
    Blob(const Blob& blob);
    Blob& operator=(const Blob& blob);

  public:
    void CopyFrom(char* mem, size_t len);

  public:
    char* data();
    size_t size();

  private:
    char* memory_;
    size_t size_;
};
};

#endif /* !BLOB_H */
