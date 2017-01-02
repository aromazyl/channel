/*
 * blob.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BLOB_H
#define BLOB_H

#include <memory>

namespace blob {
template <typename DataType>
class Blob {
  public:
    Blob(size_t size);
    ~Blob();
  public:
  private:
    char* memory_;
};
};

#endif /* !BLOB_H */
