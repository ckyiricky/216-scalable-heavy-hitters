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


class Processor
{
private:
    // Dependency injection
    std::shared_ptr<Filter> mpFilter;
    std::shared_ptr<Reporter> mpReporter;
    // TODO: DataProcessor interface
    std::shared_ptr<DataPreprocessor> mpPreprocessor;
    // Data queues
    //  input: produced by data preprocessor, consumed by filter
    //  output: produced by filter, consumed by reporter
    SafeQueue<std::shared_ptr<TVShows>> mInputDataQueue;
    SafeQueue<std::shared_ptr<TVShows>> mOutputDataQueue;
    // Three working threads
    std::shared_ptr<std::thread> mpDataThread;
    std::shared_ptr<std::thread> mpFilterThread;
    std::shared_ptr<std::thread> mpReportThread;
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
    Processor(std::shared_ptr<Filter>, std::shared_ptr<Reporter>, std::shared_ptr<DataPreprocessor>);
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
