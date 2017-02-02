#include <iostream>
#include "condition_variable.hpp"
#include <atomic>
#include <unistd.h>
#include <thread>
class Print {
  public:
    Print() {
      this->Run();
    }
  public:
    void printA() {
      int count = 3;
      while (count != 0) {
        ca_.Wait();
        printf("A\n");
        --count;
        cb_.Post();
      }
      running -= 1;
    }
    void printB() {
      int count = 3;
      while (count != 0) {
        cb_.Wait();
        printf("B\n");
        --count;
        cc_.Post();
      }
      running -= 1;
    }
    void printC() {
      int count = 3;
      while (count != 0) {
        cc_.Wait();
        printf("C\n");
        --count;
        ca_.Post();
      }
      running -= 1;
    }

    void Main() {
      auto P1 = std::thread(&Print::printA, this);
      auto P2 = std::thread(&Print::printB, this);
      auto P3 = std::thread(&Print::printC, this);
      usleep(10);
      ca_.Post();
      while (running != 0) { usleep(1000); }
      P1.join();
      P2.join();
      P3.join();
    }
    void Run() {
      running = 3;
      this->Main();
    }
  private:
    ConditionVariable ca_;
    ConditionVariable cb_;
    ConditionVariable cc_;
    std::atomic<int> running;
};

int main() {
  Print();
  return 0;
}
