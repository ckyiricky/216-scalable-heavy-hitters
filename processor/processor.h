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
    SafeQueue<std::shared_ptr<Data>> mInputDataQueue;
    SafeQueue<std::shared_ptr<Data>> mOutputDataQueue;
    // Three working threads
    std::shared_ptr<std::thread> mpDataThread;
    std::shared_ptr<std::thread> mpFilterThread;
    std::shared_ptr<std::thread> mpReportThread;
    // Thread control variables
    bool mFilterWorking;
    bool mPreDataWorking;
    bool mReportWorking;
    // Total pieces of data
    unsigned long mTotalData;
    unsigned long mProcessedData;
    // File path
    std::string mFilename;

    // Private member methods: thread working functions
    void filtering();
    void dataPreprocessing();
    void reporting();
    // Helper function
    void getList(std::string& s, std::vector<std::string>& out);
public:
    Processor() = delete;
    Processor(std::shared_ptr<Filter>, std::shared_ptr<Reporter>, std::shared_ptr<DataPreprocessor>, unsigned long totalData, const std::string& filePath);
    ~Processor(){};
    void startFiltering();
    void stopFiltering();
    void startDataPreprocessing();
    void stopDataPreprocessing();
    void startReporting();
    void stopReporting();
    void startAll();
    void stopAll();
    void joinThreads();
    void setDataSize(unsigned long size){mTotalData = size;}
    void setFilePath(const std::string& file){mFilename = file;}
};

#endif /* !PROCESSOR_H */
