#pragma once

class AutoLock {
    public:
        AutoLock(pthread_mutex_t* lock) {
            lock_ = lock;
            pthread_mutex_lock(lock_);
        }
        ~AutoLock() {
            pthread_mutex_unlock(lock_);
        }

    private:
        pthread_mutex_t* lock_;
};
