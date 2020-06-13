/*
 * reporter.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef REPORTER_H
#define REPORTER_H

#include <memory>
#include "data.h"

/*
 * This class is used to report the result.
 * TODO: Design and implementation pending
 */
class Reporter
{
public:
    virtual void report(std::shared_ptr<Data>) = 0;
};

#endif /* !REPORTER_H */
