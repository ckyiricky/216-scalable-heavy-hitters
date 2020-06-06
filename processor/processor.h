/*
 * processor.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "filter.h"

using namespace std;

class Processor
{
private:
    // Dependency injection
    shared_ptr<Filter> mFilter;
    shared_ptr<Reporter> mReporter;
    // TODO: SafeQueue implementation
    shared_ptr<SafeQueue<TVShows>> mInputDataQueue;
    shared_ptr<SafeQueue<TVShows>> mOutputDataQueue;
    // TODO: Thread implementation
    shared_ptr<thread> mFilterThread;
    shared_ptr<thread> mReportThread;
public:
    Processor();
    Processor(shared_ptr<MultistageFilter>, shared_ptr<Reporter>);
    ~Processor();
    start();
};

#endif /* !PROCESSOR_H */
