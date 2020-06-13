/*
 * heavy_hitters.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <cstdlib>
#include <fstream>

#include "processor.h"
#include "fake_reporter.h"
#include "data_preprocessor_impl.h"
#include "multistage_filter.h"
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
    if (argc < 2)
    {
        printf("Wrong parameters! \n");
        printf("Call heavy_hitter csv_file\n");
        return 0;
    }
    initLog(argv[0]);
    unsigned long total = countLines(argv[1]);
    shared_ptr<Filter> pFilter = make_shared<MultistageFilter>(3, make_shared<DefaultHasher>(), total, 0.01);
    shared_ptr<Reporter> pReporter = make_shared<FakeReporter>();
    shared_ptr<DataPreprocessor> pDataProcessor = make_shared<DataPreprocessorImpl>();
    shared_ptr<Processor> pProcessor = make_shared<Processor>(pFilter, pReporter, pDataProcessor, total, argv[1]);
    pProcessor->startAll();
    pProcessor->joinThreads();
    return 0;
}
