/*
 * naive_hash.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef NAIVE_HASH_H
#define NAIVE_HASH_H

#include "filter.h"

class NaiveFilter : public Filter
{
private:
    unsigned long mThreshold;
    std::unordered_map<std::string, unsigned long> mStat;
public:
    NaiveFilter(unsigned long t) : mThreshold(t){}
    void setConservativeUpdate(bool flag){}
    bool filter(std::shared_ptr<Data> data)
    {
        return ++mStat[data->UID] >= mThreshold;
    }
};

#endif /* !NAIVE_HASH_H */
