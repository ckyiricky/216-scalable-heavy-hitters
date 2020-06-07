/*
 * multistage_filter.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "multistage_filter.h"



MultistageFilter::MultistageFilter(int filterSize, shared_ptr<Hasher> hasher, unsigned long threshold) 
    : mHasher(hasher), mThreshold(threshold)
{
    if (filterSize <= 0)
    {
        printf("filter size < 0, automatically set to 1");
        filterSize = 1;
    }
    mFilters.resize(filterSize, vector<unsigned long>(mEntries));
    mStage = filterSize;
    // TODO: calculate mEntries, temporarily set to 10
    mEntries = 10;
}

MultistageFilter::MultistageFilter(int filterSize, shared_ptr<Hasher> hasher, unsigned long totalData, double thresholdRatio) 
    : mHasher(hasher)
{
    if (thresholdRatio > 1.0)
    {
        printf("threshold ratio > 1.0, automatically set to 1.0");
        thresholdRatio = 1.0;
    }
    mThreshold = totalData * thresholdRatio;
    if (filterSize <= 0)
    {
        printf("filter size < 0, automatically set to 1");
        filterSize = 1;
    }
    mFilters.resize(filterSize, vector<unsigned long>(mEntries));
    mStage = filterSize;
    // TODO: calculate mEntries, temporarily set to 10
    mEntries = 10;
}

~MultistageFilter::MultistageFilter()
{
}

bool MultistageFilter::filter(shared_ptr<TVShows> data, bool conservativeUpdate = false)
{
    // TODO: conservative update
    string dataId = data->getUID();
    auto hashId = mHasher(dataId);
    vector<unsigned long> hashes;
    getHashes(hashId, hashes);
    for (int i = 0; i < mStage; ++i)
    {
        if (++mFilters[i][hashes[i]%mEntries] < mThreshold)
        {
            passed = false;
        }
    }
    return passed;
}

void MultistageFilter::getHashes(unsigned long id, vector<unsigned long>& hashes)
{
    // Ad-hoc for 64 bits
    auto steps = 64 / mStages;
    bitset<64> bits(id);
    for (int i = 0; i < mStages; ++i)
    {
        unsigned long tmp = 0;
        for (int j = 0; j < steps; ++j)
        {
            if (bits.test(j+steps*i))
                tmp |= 1;
            tmp <<= 1;
        }
        hashes.push_back(tmp);
    }
}
