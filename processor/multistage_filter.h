/*
 * multistage_filter.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MULTISTAGE_FILTER_H
#define MULTISTAGE_FILTER_H

#include <vector>
#include "filter.h"
#include "hasher.h"

class MultistageFilter : public Filter
{
private:
    // TODO: structure of filters
    std::vector<std::vector<unsigned long>> mFilters;
    std::shared_ptr<Hasher> mHasher;
    unsigned long mThreshold;
    int mStages;
    // TODO: how many entries are need for every stage
    int mEntries;
    void getHashes(unsigned long id, std::vector<unsigned long>& hashes);
public:
    MultistageFilter(int filterSize, std::shared_ptr<Hasher> hasher, unsigned long threshold);
    MultistageFilter(int filterSize, std::shared_ptr<Hasher> hasher, unsigned long totalData, double thresholdRatio);
    ~MultistageFilter();
    // TODO: might not need the bool, in filter data has been put the data into the queue
    // Future update to perfect forwarding
    bool filter(std::shared_ptr<TVShows> data){return filter(data, false);}
    bool filter(std::shared_ptr<TVShows> data, bool conservativeUpdate = false);
};

#endif /* !MULTISTAGE_FILTER_H */
