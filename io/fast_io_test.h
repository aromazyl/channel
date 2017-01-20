#include <gtest/gtest.h>
#define DEBUG
#define public public
#define private public
#define protected public
#include <stdio.h>
#include "fast_io.h"

class FAST_IO_TEST : public testing::Test {
  public:
    void SetUp() {
      stream.Load("./TEST");
      stream.Init(2048, 128);
    }
  public:
    void TearDown() {}
  public:
    LineStream stream;
};

TEST_F(FAST_IO_TEST, GetLine) {
  char* buf;
  int len;
  FILE* df = fopen("./TEST1", "w");
  while (stream.GetLine(&buf, &len)) {
    fwrite(buf, 1, len, df);
  }
  fclose(df);
}
