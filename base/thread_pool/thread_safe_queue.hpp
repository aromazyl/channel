#pragma once
#include <queue>
#include <pthread.h>
/*
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/move/move.hpp>
*/
#include <memory>
#include <utility>
#include "condition_variable.hpp"
#include "AutoLock.hpp"

template <typename T>
class ThreadSafeQueue {
    private:
        pthread_mutex_t mutex_;
        std::queue<std::shared_ptr<T> > data_queue_;
        ConditionVariable cond_;

    public:
        ThreadSafeQueue() {
            pthread_mutex_init(&mutex_, NULL);
        }
        ~ThreadSafeQueue() {
            cond_.Post();
            pthread_mutex_destroy(&mutex_);
        }

        void WaitAndPop(T& value) {
            AutoLock(&(this->mutex_));
            cond_.Wait();
            value = *data_queue_.front();
            data_queue_.pop();
        }

        bool TryPop(T& value) {
            AutoLock(&(this->mutex_));
            if (data_queue_.empty()) return false;
            value = std::move(*data_queue_.front());
            data_queue_.pop();
            return true;
        }

        std::shared_ptr<T> WaitAndPop() {
            AutoLock(&(this->mutex_));
            if (data_queue_.empty()) cond_.Wait();
            std::shared_ptr<T> res = data_queue_.front();
            data_queue_.pop();
            return res;
        }

        std::shared_ptr<T> TryPop() {
            AutoLock(&(this->mutex_));
            if (data_queue_.empty()) return std::shared_ptr<T>();
            std::shared_ptr<T> res = data_queue_.front();
            data_queue_.pop();
            return res;
        }

        void Push(const T& new_value) {
            AutoLock(&(this->mutex_));
            std::shared_ptr<T> data(std::make_shared<T>(new_value));
            data_queue_.push(data);
            cond_.Post();
        }

        bool Empty() const {
            AutoLock(&(this->mutex_));
            return data_queue_.empty();
        }

};
