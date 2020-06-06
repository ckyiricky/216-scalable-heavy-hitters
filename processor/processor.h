/*
 * processor.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "multistage_filter.h"

class Processor
{
private:
    shared_ptr<MultistageFilter> mFilter;
    shared_ptr<Reporter> mReporter;
    // TODO: SafeQueue implementation
    SafeQueue<TVShows> mInputDataQueue;
    SafeQueue<TVShows> mOutputDataQueue;
    // TODO: Thread implementation
    Thread mFilterThread;
    Thread mReportThread;
public:
    Processor();
    Processor(shared_ptr<MultistageFilter>, shared_ptr<Reporter>);
    ~Processor();
    start();
};

#endif /* !PROCESSOR_H */
