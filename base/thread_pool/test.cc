/*
 * test.cc
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <functional>

std::function<int()> foo;

void *thr(void *)
{
    foo();
}

int main()
{
    pthread_t tid;
      pthread_create(&tid, nullptr, thr, nullptr);
        pthread_join(tid, nullptr);
}

