/*
 * processor.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <thread>
#include "filter.h"
#include "reporter.h"
#include "data_preprocessor.h"
#include "safe_queue.h"

using namespace std;

class Processor
{
private:
    // Dependency injection
    shared_ptr<Filter> mpFilter;
    shared_ptr<Reporter> mpReporter;
    // TODO: DataProcessor interface
    shared_ptr<DataPreprocessor> mpPreprocessor;
    // Data queues
    //  input: produced by data preprocessor, consumed by filter
    //  output: produced by filter, consumed by reporter
    SafeQueue<shared_ptr<TVShows>> mInputDataQueue;
    SafeQueue<shared_ptr<TVShows>> mOutputDataQueue;
    // Three working threads
    shared_ptr<thread> mpDataThread;
    shared_ptr<thread> mpFilterThread;
    shared_ptr<thread> mpReportThread;
    // Thread control variables
    bool mFilterWorking;
    bool mPreDataWorking;
    bool mReportWorking;

    // Private member methods: thread working functions
    void filtering();
    void dataPreprocessing();
    void reporting();
public:
    Processor() = delete;
    Processor(shared_ptr<Filter>, shared_ptr<Reporter>, shared_ptr<DataPreprocessor>);
    ~Processor(){};
    void startFiltering();
    void stopFiltering();
    void startDataPreprocessing();
    void stopDataPreprocessing();
    void startReporting();
    void stopReporting();
    void startAll();
    void stopAll();
};

#endif /* !PROCESSOR_H */
