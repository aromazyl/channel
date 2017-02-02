#pragma once

#include <pthread.h>

class ConditionVariable {
    public:
        ConditionVariable() {
            pthread_mutex_init(&lock_, NULL);
            pthread_cond_init(&cond_, NULL);
        }
        ~ConditionVariable() {
            pthread_mutex_destroy(&lock_);
            pthread_cond_destroy(&cond_);
        }

    public:
        void Wait() {
            pthread_mutex_lock(&lock_);
            pthread_cond_wait(&cond_, &lock_);
            pthread_mutex_unlock(&lock_);
        }
        void Post() {
            pthread_cond_signal(&cond_);
        }

    private:
        ConditionVariable(ConditionVariable&);
        ConditionVariable& operator=(const ConditionVariable&); 
        pthread_mutex_t lock_;
        pthread_cond_t cond_;
};
