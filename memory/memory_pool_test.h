/*
 * memory_pool_test.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MEMORY_POOL_TEST_H
#define MEMORY_POOL_TEST_H

#define public public
#define private public
#define protected public

#include "memory_pool.h"

using namespace mem;

class MemoryTest : public ::testing::Test {
  public:
    virtual void SetUp() {
      allocator = Allocator::Get();
      block = NULL;
      list = NULL;
    }
    virtual void TearDown() {}

  private:
    Allocator* allocator;
    MemoryBlock* block;
    BlockList* list;
};

TEST_F(MemoryTest, AllocatorConstructionTest) {
}

TEST_F(MemoryTest, AllocatorAllocTest) {
  char* tmp = allocator->Alloc(100);
  ASSERT_TRUE(tmp);
  ASSERT_TRUE(allocator->pool_.count(tmp) == 1);
  allocator->Free(tmp);
  char* t2 = allocator->Alloc(110);
  ASSERT_TRUE(tmp == t2);
  tmp = allocator->Alloc(0);
  EXPECT_EQ(allocator->pool_.size(), static_cast<size_t>(2));
}

TEST_F(MemoryTest, FreeAllocTest) {
}

#endif /* !MEMORY_POOL_TEST_H */
