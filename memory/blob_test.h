/*
 * blob_test.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BLOB_TEST_H
#define BLOB_TEST_H

#define public public
#define protected public
#define private public

#include <gtest/gtest.h>
#include "blob.h"

namespace blob {

class BlobTest : public ::testing::Test {
  public:
    virtual void SetUp() {}
    virtual void TearDown() {}

  private:
    Blob* blob;
};

TEST_F(BlobTest, SimpleConstructionTest) {
  blob = new Blob(128);
  delete blob;
}

TEST_F(BlobTest, ResizeTest) {
  blob = new Blob(256);
  EXPECT_EQ(blob->size(), 256);
  blob->resize(128);
  EXPECT_EQ(blob->size(), 128);
  delete blob;
}

TEST_F(BlobTest, CopyFrom_To) {
  blob = new Blob(128);
  blob2 = new Blob(200);
  blob.CopyFrom("i love u", sizeof("i love u"));
  blob.CopyTo(blob2.data(), blob2.size());
  printf("blob1 : %s\n", blob1.data());
  printf("blob2 : %s\n", blob2.data());
}

}

#endif /* !BLOB_TEST_H */
