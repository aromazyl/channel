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
#include "./server.h"
#include "./client.h"

#include <thread>
#include <mutex>


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  if (std::string(argv[1]) == "server") {
    server_run();
  } else {
    client_run();
  }
  return RUN_ALL_TESTS();
}
