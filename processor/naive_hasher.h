#ifndef NAIVE_HASHER_H
#define NAIVE_HASHER_H

#include <vector>
#include <unordered_map>
#include "hasher.h"
#include "filter.h"

class NaiveHasher: public Filter
{
private:
    std::unordered_map<unsigned long,unsigned long> mHashTable;
    std::shared_ptr<Hasher> mHasher;
    unsigned long mThreshold;
public:
    NaiveHasher(std::shared_ptr<Hasher> hasher, unsigned long threshold);
    bool filter(std::shared_ptr<TVShows> data);
    ~NaiveHasher();
};

#endif
