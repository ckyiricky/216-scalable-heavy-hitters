#ifndef NAIVE_HASHER_H
#define NAIVE_HASHER_H

#include <vector>
#include <list>
#include <unordered_map>
#include "hasher.h"
#include "filter.h"

struct entry {
    std::string id;
    unsigned long count;
}

class NaiveHasher: public Filter
{
private:
    std::unordered_map<unsigned long,std::list<entry>> mHashTable;
    std::shared_ptr<Hasher> mHasher;
    unsigned long mThreshold;
public:
    NaiveHasher(std::shared_ptr<Hasher> hasher, unsigned long threshold);
    bool filter(std::shared_ptr<TVShows> data);
    ~NaiveHasher();
};

#endif
