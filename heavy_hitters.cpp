/*
 * heavy_hitters.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <cstdlib>
#include <fstream>
#include <iterator>
#include <chrono>
#include <algorithm>
#include <vector>

#include "processor.h"
#include "count_reporter.h"
#include "data_preprocessor_impl.h"
#include "multistage_filter.h"
#include "sample_and_hold.h"
#include "naive_filter.h"
#include "default_hasher.h"
#include "log.h"

/*
 * IMPORTANT: This is a test version, sleep is for test only
 */
using namespace std;

int countLines(char* file)
{
    std::ifstream myfile(file);
    // new lines will be skipped unless we stop it from happening:
    myfile.unsetf(std::ios_base::skipws);
    // count the newlines with an algorithm specialized for counting:
    unsigned long total = std::count(
        std::istream_iterator<char>(myfile),
        std::istream_iterator<char>(),
        '\n');
    myfile.close();
    return total;
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        printf("Wrong parameters! \n");
        printf("Call heavy_hitter csv_file output_directory threshold\n");
        return 0;
    }
    initLog(argv[0]);
    makeDir(argv[2]);
    unsigned long total = countLines(argv[1]);
    string output = argv[2];
    double threshold = stod(argv[3]);
    // Change data id keys
    vector<int> keys = {0};

    shared_ptr<Filter> pFilter = make_shared<MultistageFilter>(3, make_shared<DefaultHasher>(), total, threshold);
    shared_ptr<Reporter> pReporter = make_shared<CountReporter>(output + "/multistage_conservative_update.report");
    shared_ptr<DataPreprocessor> pDataProcessor = make_shared<DataPreprocessorImpl>();
    shared_ptr<Processor> pProcessor = make_shared<Processor>(pFilter, pReporter, pDataProcessor, total, argv[1]);
    pProcessor->setDataKeys(keys);
    auto start = chrono::steady_clock::now();
    pProcessor->startAll();
    pProcessor->joinThreads();
    auto end = chrono::steady_clock::now();
    chrono::duration<double> dur = end - start;
    printf("Processing time for multistage with conservative update: %f \n", dur.count());

    pProcessor->reset();
    pFilter->setConservativeUpdate(false);
    pReporter.reset(new CountReporter(output + "/multistage.report"));
    pProcessor->setReporter(pReporter);
    start = chrono::steady_clock::now();
    pProcessor->startAll();
    pProcessor->joinThreads();
    end = chrono::steady_clock::now();
    dur = end - start;
    printf("Processing time for multistage without conservative update: %f \n", dur.count());

    pProcessor->reset();
    pFilter.reset(new SampleAndHold((unsigned long)total*threshold));
    pReporter.reset(new CountReporter(output + "/sample_and_hold.report"));
    pProcessor->setFilter(pFilter);
    pProcessor->setReporter(pReporter);

    start = chrono::steady_clock::now();
    pProcessor->startAll();
    pProcessor->joinThreads();
    end = chrono::steady_clock::now();
    dur = end - start;
    printf("Processing time for sample and hold: %f \n", dur.count());

    pProcessor->reset();
    pFilter.reset(new NaiveFilter((unsigned long)total*threshold));
    pReporter.reset(new CountReporter(output + "/naive.report"));
    pProcessor->setFilter(pFilter);
    pProcessor->setReporter(pReporter);

    start = chrono::steady_clock::now();
    pProcessor->startAll();
    pProcessor->joinThreads();
    end = chrono::steady_clock::now();
    dur = end - start;
    printf("Processing time for naive hashing: %f \n", dur.count());

    return 0;
}
