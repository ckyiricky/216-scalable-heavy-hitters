/*
 * filter.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef FILTER_H
#define FILTER_H

#include <memory>
#include "common.h"

class Filter
{
public:
    virtual bool filter(std::shared_ptr<TVShows> data) = 0;
    virtual ~Filter(){}
};

#endif /* !FILTER_H */
