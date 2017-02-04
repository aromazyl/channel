#pragma once
#include <vector>
#include <functional>
#include <thread>
#include <atomic>
#include "thread_safe_queue.hpp"
#include "condition_variable.hpp"

class ThreadPool {
    public:
        ThreadPool(): done_(false) {
            unsigned const thread_count = std::thread::hardware_concurrency();
            try {
                for (unsigned i = 0; i < thread_count; ++i) {
                    threads_.push_back(std::thread(&ThreadPool::WorkerThread, this));
                }
            } catch (...) {
                done_ = true;
                throw;
            }
        }

        ~ThreadPool() {
            done_ = true;
            for (size_t i = 0; i < threads_.size(); ++i) {
                threads_[i].join();
            }
        }

    public:
        template <typename FunctionType>
        void Submit(FunctionType f) {
            queue_.Push(std::function<void()>(f));
        }

    private:
        void WorkerThread() {
            while (!done_) {
                std::function<void()> task;
                if (queue_.TryPop(task)) {
                    task();
                } else {
                  std::this_thread::yield();
                }
            }
        }

    private:
        std::atomic_bool done_;
        ThreadSafeQueue<std::function<void()>> queue_;
        std::vector<std::thread> threads_;
};
