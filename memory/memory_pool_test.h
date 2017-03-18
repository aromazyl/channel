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

#include "memory/blob.h"
#include "memory/memory_pool.h"

class MemoryTest : public ::testing::Test {
  public:
    virtual void SetUp() {
      allocator = new mem::Allocator();
      block = NULL;
      list = NULL;
    }
    virtual void TearDown() {}

  private:
    mem::Allocator* allocator;
    mem::MemoryBlock* block;
    mem::BlockList* list;
};

TEST_F(MemoryTest, AllocatorConstructionTest) {
};

TEST_F(MemoryTest, AllocatorAllocTest) {
  char* tmp = allocator->Alloc(100);
  ASSERT_TRUE(tmp);
  ASSERT_TRUE(static_cast<bool>(allocator->pool_.count(128)));
  allocator->Free(tmp);
  char* t2 = allocator->Alloc(110);
  EXPECT_EQ(tmp, t2);
  tmp = allocator->Alloc(0);
  EXPECT_EQ(allocator->pool_.size(), static_cast<size_t>(2));
};

TEST_F(MemoryTest, FreeAllocTest) {
  char* tmp = allocator->Alloc(100);
  char* t = allocator->Refer(tmp);
  allocator->Free(t);
  allocator->Free(tmp);
};

TEST_F(MemoryTest, BlockListTest) {
  list = new mem::BlockList(100);
  block = new mem::MemoryBlock(100, list);
  list->Push(block);
  EXPECT_EQ((*(void**)(block->data_)), (void*)block);
  delete list;
  list = NULL;
}

#endif /* !MEMORY_POOL_TEST_H */
