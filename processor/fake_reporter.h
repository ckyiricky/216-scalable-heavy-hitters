/*
 * fake_reporter.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef FAKE_REPORTER_H
#define FAKE_REPORTER_H

#include "reporter.h"

class FakeReporter : public Reporter
{
public:
    void report(std::shared_ptr<Data>);
    ~FakeReporter(){}
};

#endif /* !FAKE_REPORTER_H */
