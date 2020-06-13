#ifndef NAIVE_HASHER_H
#define NAIVE_HASHER_H

#include <vector>
#include "hasher.h"

class NaiveHasher
{
private:
    std::unordered_map<unsigned long,unsigned long> hashTable;
    std::shared_ptr<Hasher> mHasher;
    unsigned long mThreshold;
public:
    NaiveHasher(std::shared_ptr<Hasher> hasher, unsigned long threshold);
    bool NaiveHasher::filter(shared_ptr<TVShows> data);
    ~NaiveHasher();
};

#endif