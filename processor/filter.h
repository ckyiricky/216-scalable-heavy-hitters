/*
 * filter.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef FILTER_H
#define FILTER_H

#include <memory>
#include "data.h"

class Filter
{
public:
    virtual void setConservativeUpdate(bool) = 0;
    virtual bool filter(std::shared_ptr<Data> data) = 0;
    virtual ~Filter(){}
};

#endif /* !FILTER_H */
