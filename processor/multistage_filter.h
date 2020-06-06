/*
 * multistage_filter.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MULTISTAGE_FILTER_H
#define MULTISTAGE_FILTER_H

#include <vector>
#include <shared_ptr>
#include "common.h"

class MultistageFilter
{
private:
    vector<unordered_map<string, unsigned long>> mFilters;
    /*
    SafeQueue<TVShows> mInputDataQueue;
    SafeQueue<TVShows> mOutputDataQueue;
    */
    shared_ptr<Hasher> mHasher;
    unsigned long mThreshold;
public:
    MultistageFilter(int filterSize, shared_ptr<Hasher> hasher, unsigned long threshold);
    MultistageFilter(int filterSize, shared_ptr<Hasher> hasher, unsigned long totalData, double thresholdRatio);
    ~MultistageFilter();
    bool filter(const TVShows& data, bool conservativeUpdate = false);
};

#endif /* !MULTISTAGE_FILTER_H */
