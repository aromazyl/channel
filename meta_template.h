/*
 * message.h
 * Copyright (C) 2016 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MESSAGE_H
#define MESSAGE_H

namespace proto {
template <int Val>
struct IntType {
  enum { Value = Val };
};

template <bool val>
struct BoolType;

template <>
struct BoolType<true> {
  using Result = typename IntType<true>::Value;
};

template <>
struct BoolType<false> {
  using Result = typename IntType<false>::Value;
};

template <typename T1, typename T2>
struct IsSameType {
  using Result = BoolType<false>
};

template <typename T>
struct IsSameType<T, T> {
  using Result = BoolType<true>;
};

template <typename T, typename ActA, typename ActB>
struct IfThenElse;

template <typename ActA, typename ActB>
struct IfThenElse<BoolType<true>, ActA, ActB> {
  using Result = typename ActA::Result;
};

template <typename ActA, typename ActB>
struct IfThenElse<BoolType<false>, ActA, ActB> {
  using Result = typename ActB::Result;
};

#endif /* !MESSAGE_H */
