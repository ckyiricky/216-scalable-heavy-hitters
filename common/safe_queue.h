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
#include <memory>

/*
 * Thread safe queue, one producer and one customer
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
    void push(const T& data)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mQueue.push(data);
        mCondition.notify_one();
    }
    void push(T&& data)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mQueue.push(data);
        mCondition.notify_one();
    }
    const T& pop()
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mCondition.wait(lock, [&]{return !mQueue.empty();});
        T val = mQueue.front();
        mQueue.pop();
        return val;
    }
    bool tryPop(T& outputData)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        if (mQueue.empty())
        {
            return false;
        }
        outputData = mQueue.front();
        mQueue.pop();
        return true;
    }
    bool empty()
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return mQueue.empty();
    }
};

#endif /* !SAFE_QUEUE_H */
