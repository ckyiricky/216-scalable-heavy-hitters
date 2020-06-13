
#include <bitset>
#include "log.h"
#include "naive_hasher.h"

using namespace std;

NaiveHasher::NaiveHasher(shared_ptr<Hasher> hasher, unsigned long threshold) 
    : mHasher(hasher), mThreshold(threshold)
{
}

NaiveHasher::~NaiveHasher()
{
}

bool NaiveHasher::filter(shared_ptr<TVShows> data)
{
    string dataId = data->getUID();
    auto hashId = mHasher->hash(dataId);
    if (mHashTable.count(hashId) > 0) {
        if (++mHashTable[hashId] > mThreshold)
            return false;
    } else 
        mHashTable[hashId] = 1;
    return true;
}
