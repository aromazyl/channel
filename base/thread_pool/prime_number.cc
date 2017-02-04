#include <stdio.h>
#include <stdlib.h>

#include <functional>
#include <atomic>
#include <algorithm>
#include <unistd.h>
// #include "condition_variable.hpp"
#include <condition_variable>
#include <memory>
#include <mutex>

#include "simple_threadpool.hpp"

// ConditionVariable cond;
std::unique_ptr<std::mutex> mu_ptr;
std::condition_variable cond;

bool IsPrime(long num) {
  for (long i = 2; i * i < num; ++i) {
    if (num - num / i * i == 0) return false;
  }
  return true;
}

void CalPrimNums(long st, long end, int* numbers, std::atomic<int>* counter) {
  *numbers = 0;
  for (; st <= end; ++st) {
    if (IsPrime(st)) ++(*numbers);
  }
  ++*counter;
}

int main(int argc, char* argv[]) {
  ThreadPool pool;
  long num = 9999999;
  int split = 8;
  int result[8] = {0};
  std::atomic<int> counter(0);
  printf("init \n");
  for (int i = 0; i <= 7; ++i) {
    long st = i * num / split;
    long end = std::min(num, (i + 1) * num / split);
    pool.Submit(std::bind(CalPrimNums, st, end, result + i, &counter));
    printf("submit:%d\n", i);
  }
  while (counter != 8) {
    usleep(1000);
  }
  for (auto& k : result) {
    printf("k:%d\n", k);
  }
  return 0;
}
