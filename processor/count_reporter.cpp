/*
 * count_reporter.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <fstream>
#include "log.h"
#include "count_reporter.h"

using namespace std;

CountReporter::CountReporter()
    : CountReporter("./report.txt")
{
}

CountReporter::CountReporter(const string& file)
{
    mOfs.open(file);
    if (!mOfs.good())
    {
        LOG(ERROR) << "Open output file " << file << " failed";
    }
}

CountReporter::~CountReporter()
{
    mOfs.close();
}

void CountReporter::report(std::shared_ptr<Data> data)
{
    string dataString;
    for (auto& s : data->data)
    {
        // Ad-hoc sovle the windows line end chars
        if (s.size() < 2 && isspace(s[0]))
            continue;
        dataString += s + ", ";
    }
    if (mOfs.good())
        mOfs << "Data id : " << dataString.erase(dataString.size() - 2) << endl;
    else
        LOG(FATAL) << "Output file broken";
}
