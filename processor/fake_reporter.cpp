/*
 * fake_reporter.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "log.h"
#include "fake_reporter.h"

void FakeReporter::report(std::shared_ptr<TVShows> data)
{
    LOG(INFO) << "Data id : " << data->getUID();
}
