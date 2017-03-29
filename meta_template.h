/*
 * message.h
 * Copyright (C) 2016 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MESSAGE_H
#define MESSAGE_H

template <int Val>
struct IntType {
  enum { Value = Val };
};

template <bool val>
struct BoolType;

template <>
struct BoolType<true> {
  using Result = IntType<true>;
};

template <>
struct BoolType<false> {
  using Result = IntType<false>;
};

template <typename T1, typename T2>
struct IsSameType {
  using Result = BoolType<false>;
};

template <typename T>
struct IsSameType<T, T> {
  using Result = BoolType<true>;
};

template <typename T, typename ActA, typename ActB>
struct IfThenElse;

template <bool type, typename ActA, typename ActB>
struct IfThenElse<BoolType<type>, ActA, ActB> {
  using Result = typename ActA::Result;
};

template <typename ActA, typename ActB>
struct IfThenElse<BoolType<false>, ActA, ActB> {
  using Result = typename ActB::Result;
};

// static show
template <int Value>
struct Print {
  operator char() {
    return Value + 0xff;
  }
};

#define __print(token, ...) do { char print_value_##token = Print<__VA_ARGS__>(); \
  print_value_##token = 0; } while (0)

#endif /* !MESSAGE_H */
