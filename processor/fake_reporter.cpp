/*
 * fake_reporter.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "fake_reporter.h"


void FakeReporter::report(shared_ptr<TVShows> data)
{
    printf("data id %s \n", data->getUID().c_str());
}
