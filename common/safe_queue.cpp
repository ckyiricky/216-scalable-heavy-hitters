/*
 * safe_queue.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "safe_queue.h"


template<class T>
void SafeQueue<T>::push(const T& data)
{
    std::lock_guard<std::mutex> lock(mMutex);
    mQueue.push(data);
    mCondition.notify_one();
}
template<class T>
void SafeQueue<T>::push(T&& data)
{
    std::lock_guard<std::mutex> lock(mMutex);
    mQueue.push(data);
    mCondition.notify_one();
}
template<class T>
T SafeQueue<T>::pop()
{
    std::lock_guard<std::mutex> lock(mMutex);
    mCondition.wait(lock, [&]{return !mQueue.empty();});
    T val = mQueue.front();
    mQueue.pop();
    return val;
}
template<class T>
bool SafeQueue<T>::tryPop(T& outputData)
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
template<class T>
bool SafeQueue<T>::empty()
{
    std::lock_guard<std::mutex> lock(mMutex);
    return mQueue.empty();
}
