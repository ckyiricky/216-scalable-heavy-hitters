/*
 * heavy_hitters.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <chrono>

#include "processor.h"
#include "fake_reporter.h"
#include "fake_preprocessor.h"
#include "multistage_filter.h"
#include "default_hasher.h"
#include "log.h"

/*
 * IMPORTANT: This is a test version, sleep is for test only
 */
using namespace std;

int main(int argc, char* argv[])
{
    initLog(argv[0]);
    shared_ptr<Filter> pFilter = make_shared<MultistageFilter>(3, make_shared<DefaultHasher>(), 10);
    shared_ptr<Reporter> pReporter = make_shared<FakeReporter>();
    shared_ptr<DataPreprocessor> pDataProcessor = make_shared<FakePreprocessor>();
    shared_ptr<Processor> pProcessor = make_shared<Processor>(pFilter, pReporter, pDataProcessor);
    pProcessor->startAll();
    this_thread::sleep_for(chrono::seconds(5));
    pProcessor->stopAll();
    return 0;
}
