/*
 * feature_type.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef FEATURE_TYPE_H
#define FEATURE_TYPE_H

#include <vector>

struct Weights {
  std::vector<uint64_t> fid;
  std::vector<int> lens;
  std::vector<char> weights;
};

#endif /* !FEATURE_TYPE_H */
