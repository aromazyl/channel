/*
 * test.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <gtest/gtest.h>
#include "../net/zmq_network_test.h"
#include "../memory/blob_test.h"
#include "../memory/memory_pool_test.h"


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
