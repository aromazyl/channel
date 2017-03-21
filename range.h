/*
 * range.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef RANGE_H
#define RANGE_H

#include "./meta_template.h"

template <uint64_t st, uint64_t ed> struct Range {
  static const uint64_t left = st;
  static const uint64_t right = ed;
};

template <uint64_t num>
struct Range<num> {
  static const uint64_t left = num;
  static const uint64_t right = num;
};

template <typename T> struct Func;

template <uint64_t st, uint64_t ed>
struct Func<Range<st, ed>> {
  bool WithIn(uint64_t num) const {
    return num >= st && num < ed;
  }
};

template <typename T> struct ValidRange;
template <uint64_t st, uint64_t ed>
struct ValidRange<Range<st, ed>> {
  using Result = typename BoolType<ed > st>::Result;
};

#endif /* !RANGE_H */
