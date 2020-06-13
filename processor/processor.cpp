/*
 * processor.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <fstream>
#include <chrono>
#include "processor.h"
#include "log.h"

/*
 * TODO:Methods related to data preprocessing and report have not been implemented yet
 */
using namespace std;

void Processor::getList(std::string& s, std::vector<std::string>& out)
{
	size_t pos = 0;
	while ((pos = s.find(", ")) != string::npos)
    {
		string token = s.substr(0, pos);
		out.push_back(move(token));
		s.erase(0, pos + 2);
	}
	if (s.length() > 0)
		out.push_back(s);
}

void Processor::dataPreprocessing()
{
    LOG(INFO) << "start data preprocessing";

	ifstream fin(mFilename);
	if (!fin.is_open())
    {
        LOG(ERROR) << "Open file " << mFilename << " failed!";
        stopAll();
        return;
    }
    else LOG(INFO) << "Open file " << mFilename << " succeed";
	string line;
	// Initialize categories, size and UID_keys
	getline(fin, line);
	vector<string> strs;
    getList(line, strs);
    vector<string> categories;
	for (auto& s : strs)
		categories.push_back(s);
	int size= categories.size();
    vector<int> keys = {0};
    void* attributes[] = {(void*)(&size), (void*)(&categories), (void*)(&keys)};
    mpPreprocessor->init(attributes);

	// Iterate through file and create Data object
	while (mPreDataWorking && !fin.eof())
    {
		getline(fin, line);
		if (line.length() > 0)
        {
            shared_ptr<Data> data = mpPreprocessor->preprocess(line);
            mInputDataQueue.push(data);
		}
	}

	fin.close();
}

void Processor::filtering()
{
    LOG(INFO) << "start filtering";
    while (mFilterWorking && mProcessedData < mTotalData)
    {
        shared_ptr<Data> data;
        bool getData = mInputDataQueue.tryPop(data);
        if (!getData) continue;
        bool passed = mpFilter->filter(data);
        ++mProcessedData;
        if (passed)
        {
            LOG(INFO) << "Data " << data->UID << " passed filter.";
            mOutputDataQueue.push(data);
        }
    }
}

void Processor::reporting()
{
    LOG(INFO) << "start reporting";
    shared_ptr<Data> data;
    while (mReportWorking)
    {
        bool getData = mOutputDataQueue.tryPop(data);
        if (!getData) continue;
        mpReporter->report(data);
    }
}

/*-------------------------public methods---------------------------*/

Processor::Processor(shared_ptr<Filter> filter, shared_ptr<Reporter> reporter, shared_ptr<DataPreprocessor> preprocessor, unsigned long totalData, const string& file)
    : mpFilter(filter), mpReporter(reporter), mpPreprocessor(preprocessor), mInputDataQueue(SafeQueue<shared_ptr<Data>>()), mOutputDataQueue(SafeQueue<shared_ptr<Data>>()), mTotalData(totalData), mProcessedData(0), mFilename(file)
{
}

void Processor::startDataPreprocessing()
{
    if (mPreDataWorking)
    {
        LOG(INFO) << "Datapreprocessing thread is already running";
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
        LOG(INFO) << "Filtering thread is already running";
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
        LOG(INFO) << "Reporting thread is already running";
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

void Processor::joinThreads()
{
    mpDataThread->join();
    mpFilterThread->join();
    LOG(INFO) << "All data has been filtered, waiting for reporter...";
    while (!mOutputDataQueue.empty()) this_thread::sleep_for(chrono::seconds(1));
    stopReporting();
}
