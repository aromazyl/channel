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
    explicit Blob(size_t size);
    explicit Blob(const Blob& blob);
    Blob& operator=(const Blob& blob);
    ~Blob();

  public:
    int CopyFrom(char* mem, size_t len);
    int CopyTo(char* mem, size_t len) const;

  public:
    char* data() const;
    size_t size() const;
    void resize(size_t size);

  private:
    char* memory_;
    size_t size_;
};
};

#endif /* !BLOB_H */
