/*
 * count_reporter.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef COUNT_REPORTER_H
#define COUNT_REPORTER_H

#include "reporter.h"

using ofs=std::ofstream;

class CountReporter : public Reporter
{
private:
    ofs mOfs;
public:
    CountReporter();
    CountReporter(const std::string&);
    ~CountReporter();
    void report(std::shared_ptr<Data>);
};

#endif /* !COUNT_REPORTER_H */
