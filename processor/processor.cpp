/*
 * processor.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "processor.h"

/*
 * TODO:Methods related to data preprocessing and report have not been implemented yet
 */

void Processor::dataPreprocessing()
{
    printf("start data preprocessing \n");
    shared_ptr<TVShows> data;
    while (mPreDataWorking)
    {
        shared_ptr<TVShows> data = mpPreprocessor->preprocess();
        mInputDataQueue.push(data);
    }
}

void Processor::filtering()
{
    printf("start filtering \n");
    while (mFilterWorking)
    {
        shared_ptr<TVShows> data;
        bool getData = mInputDataQueue.tryPop(data);
        if (!getData) continue;
        bool passed = mpFilter->filter(data);
        if (passed)
        {
            printf("Data %s passed filter \n", data->getUID().c_str());
            mOutputDataQueue.push(data);
        }
    }
}

void Processor::reporting()
{
    printf("start reporting \n");
    shared_ptr<TVShows> data;
    while (mReportWorking)
    {
        bool getData = mOutputDataQueue.tryPop(data);
        if (!getData) continue;
        mpReporter->report(data);
    }
}

/*-------------------------public methods---------------------------*/

Processor::Processor(shared_ptr<Filter> filter, shared_ptr<Reporter> reporter, shared_ptr<DataPreprocessor> preprocessor)
    : mpFilter(filter), mpReporter(reporter), mpPreprocessor(preprocessor), mInputDataQueue(SafeQueue<shared_ptr<TVShows>>()), mOutputDataQueue(SafeQueue<shared_ptr<TVShows>>())
{
}

void Processor::startDataPreprocessing()
{
    if (mPreDataWorking)
    {
        printf("Datapreprocessing thread is already running");
        return;
    }
    mPreDataWorking = true;
    mpDataThread = make_shared<thread>(&Processor::dataPreprocessing, this);
}

void Processor::stopDataPreprocessing()
{
    if (!mPreDataWorking) return;
    mPreDataWorking = false;
    mpDataThread->join();
}

void Processor::startFiltering()
{
    if (mFilterWorking)
    {
        printf("Filtering thread is already running");
        return;
    }
    mFilterWorking = true;
    mpFilterThread = make_shared<thread>(&Processor::filtering, this);
}

void Processor::stopFiltering()
{
    if (!mFilterWorking) return;
    mFilterWorking = false;
    mpFilterThread->join();
}

void Processor::startReporting()
{
    if (mReportWorking)
    {
        printf("Reporting thread is already running");
        return;
    }
    mReportWorking = true;
    mpReportThread = make_shared<thread>(&Processor::reporting, this);
}

void Processor::stopReporting()
{
    if (!mReportWorking) return;
    mReportWorking = false;
    mpReportThread->join();
}

void Processor::startAll()
{
    startDataPreprocessing();
    startFiltering();
    startReporting();
}

void Processor::stopAll()
{
    stopDataPreprocessing();
    stopFiltering();
    stopReporting();
}
