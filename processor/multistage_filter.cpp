/*
 * multistage_filter.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <bitset>
#include <algorithm>
#include "log.h"
#include "multistage_filter.h"

using namespace std;

MultistageFilter::MultistageFilter(int filterSize, shared_ptr<Hasher> hasher, unsigned long threshold) 
    : mHasher(hasher), mThreshold(threshold), mConservativeUpdate(true)
{
    if (filterSize <= 0)
    {
        LOG(WARNING) << "filter size < 0, automatically set to 1";
        filterSize = 1;
    }
    mStages = filterSize;
    // Without threshold ratio, roughly set to 1k, this constructor is not accurate
    mEntries = 1000;
    mFilters.resize(filterSize, vector<unsigned long>(mEntries));
}

MultistageFilter::MultistageFilter(int filterSize, shared_ptr<Hasher> hasher, unsigned long totalData, double thresholdRatio) 
    : mHasher(hasher), mConservativeUpdate(true)
{
    if (thresholdRatio > 1.0)
    {
        LOG(WARNING) << "threshold ratio > 1.0, automatically set to 1.0";
        thresholdRatio = 1.0;
    }
    mThreshold = totalData * thresholdRatio;
    if (filterSize <= 0)
    {
        LOG(WARNING) << "filter size < 0, automatically set to 1";
        filterSize = 1;
    }
    mStages = filterSize;
    // Set entries to 1/ratio * 10
    mEntries = 10/thresholdRatio;
    mFilters.resize(filterSize, vector<unsigned long>(mEntries));
}

MultistageFilter::~MultistageFilter()
{
}

bool MultistageFilter::filter(shared_ptr<TVShows> data)
{
    string dataId = data->getUID();
    auto hashId = mHasher->hash(dataId);
    vector<unsigned long> hashes;
    getHashes(hashId, hashes);
    bool passed = true;
    unsigned long minCounter = ULONG_MAX;
    for (int i = 0; i < mStages; ++i)
    {
        auto currentCounter = ++mFilters[i][hashes[i]%mEntries];
        if (currentCounter < mThreshold)
        {
            passed = false;
        }
        if (mConservativeUpdate)
            minCounter = min(currentCounter, minCounter);
    }
    if (mConservativeUpdate)
    {
        for (int i = 0; i < mStages; ++i)
        {
            if (!passed && mFilters[i][hashes[i]%mEntries] > minCounter)
                --mFilters[i][hashes[i]%mEntries];
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
