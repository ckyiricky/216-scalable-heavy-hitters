/*
 * fake_reporter.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef FAKE_REPORTER_H
#define FAKE_REPORTER_H

#include "reporter.h"
#include "common.h"

class FakeReporter : public Reporter
{
public:
    void report(shared_ptr<TVShows>);
    ~FakeReporter(){}
};

#endif /* !FAKE_REPORTER_H */
