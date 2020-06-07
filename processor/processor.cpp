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
}

void Processor::filtering()
{
    shared_ptr<TVShows> data;
    while (mFilterWorking)
    {
        bool getData = mInputDataQueue.tryPop(data);
        if (!getData) continue;
        bool passed = mFilter->filter(data);
        if (passed)
        {
            mOutputQueue.push(data);
        }
    }
}

void reporting()
{
}

/*-------------------------public methods---------------------------*/

Processor::Processor(shared_ptr<Filter> filter, shared_ptr<Reporter> reporter, shared_ptr<DataProcessor> preprocessor)
    : mpFilter(filter), mpReporter(reporter), mpPreprocessor(preprocessor)
{
    mInputDataQueue = SafeQueue<shared_ptr<TVShows>>();
    mOutputDataQueue = SafeQueue<shared_ptr<TVShows>>();
}

void Processor::startDataPreprocessing()
{
}

void Processor::stopDataPreprocessing()
{
}

void Processor::startFiltering()
{
    if (mFilterWorking)
    {
        printf("Filtering thread is already running");
        return;
    }
    mFilterWorking = true;
    mFilterThread = make_shared<thread>(&Processor::filterOneData, this);
}

void Proessor::stopFiltering()
{
    if (!mFilterWorking) return;
    mFilterThread->join();
}

void Processor::startReporting()
{
}

void Processor::stopReporting()
{
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
