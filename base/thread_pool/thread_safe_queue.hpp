#pragma once
#include <queue>
#include <mutex>
/*
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/move/move.hpp>
*/
#include <memory>
#include <utility>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
    private:
      mutable std::mutex mutex_;
      std::queue<std::shared_ptr<T> > data_queue_;
      std::condition_variable cond_;

    public:
      ThreadSafeQueue() {
      }
      ~ThreadSafeQueue() {
      }

      void WaitAndPop(T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this]{ return !data_queue_.empty(); });
        value = std::move(*data_queue_.front());
        data_queue_.pop();
      }

      bool TryPop(T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (data_queue_.empty()) return false;
        value = std::move(*data_queue_.front());
        data_queue_.pop();
        return true;
      }

      std::shared_ptr<T> WaitAndPop() {
        std::unique_lock<std::mutex> lock(mutex_);
        if (data_queue_.empty()) cond_.wait(lock, [this]{ return !data_queue_.empty(); });
        std::shared_ptr<T> res = data_queue_.front();
        data_queue_.pop();
        return res;
      }

      std::shared_ptr<T> TryPop() {
        std::unique_lock<std::mutex> lock(mutex_);
        if (data_queue_.empty()) return std::shared_ptr<T>();
        std::shared_ptr<T> res = data_queue_.front();
        data_queue_.pop();
        return res;
      }

      void Push(const T& new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(new_value));
        std::unique_lock<std::mutex> lock(mutex_);
        data_queue_.push(data);
        cond_.notify_one();
      }

      bool Empty() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return data_queue_.empty();
      }

};
