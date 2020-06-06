/*
 * safe_queue.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SAFE_QUEUE_H
#define SAFE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

/*
 * Thread safe queue
 * pop api might change
 */
template <class T>
class SafeQueue
{
private:
    std::queue<T> mQueue;
    mutable std::mutex mMutex;
    std::condition_variable mCondition;
public:
    SafeQueue(){};
    ~SafeQueue(){};
    void push(const T& data);
    void push(T&& data);
    T pop();
    bool tryPop(T& outputData);
    bool empty();
};

#endif /* !SAFE_QUEUE_H */
