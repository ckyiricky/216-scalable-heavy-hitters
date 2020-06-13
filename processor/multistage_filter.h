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

/*
 * optimization:
 *  shielding
 *  conservative update
 *      update min counter
 *      once passed no counter updated
 */

class MultistageFilter : public Filter
{
private:
    std::vector<std::vector<unsigned long>> mFilters;
    std::shared_ptr<Hasher> mHasher;
    unsigned long mThreshold;
    int mStages;
    /*
     * How many entries are need for every stage:
     *      roughly use 1 / threshold_ratio * 10
     *      The second constructor is recommended
    */
    int mEntries;
    // Default set to true: filter use conservative updated version
    bool mConservativeUpdate;
    void getHashes(unsigned long id, std::vector<unsigned long>& hashes);
public:
    MultistageFilter(int filterSize, std::shared_ptr<Hasher> hasher, unsigned long threshold);
    MultistageFilter(int filterSize, std::shared_ptr<Hasher> hasher, unsigned long totalData, double thresholdRatio);
    ~MultistageFilter();
    // TODO: Future update to perfect forwarding
    bool filter(std::shared_ptr<Data> data);
    void setConservativeUpdate(bool flag){mConservativeUpdate = flag;}
};

#endif /* !MULTISTAGE_FILTER_H */
