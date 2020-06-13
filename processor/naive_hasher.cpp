
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
    std::list<entry> mHashEntries = mHashTable[hashId];
    std::list<entry> newHashEntries; // new list, not very efficient but whatever
    std::list<entry>::iterator it;
    bool found = false;
    bool passed = true;
    // find entry in hash table bucket if it exists
    for (it = mHashEntries.begin(); it != mHashEntries.end(); ++it){
        // might be pointer errors, I'm not sure
        if (it->id.equals(dataId)) {
            entry mHashEntry;
            mHashEntry.id = it->id;
            mHashEntry.count = it->count + 1;
            newHashEntries.push_back(mHashEntry);
            found = true;
            if (mHashEntry.count > mThreshold) 
                passed = false;
        } else
            newHashEntries.push_back(*it)
    }
    mHashTable[hashId] = newHashEntries;
    if (!found) {
        entry mHashEntry;
        mHashEntry.id = dataId;
        mHashEntry.count = 1;
        mHashTable[hashId].push_back(mHashEntry);
    }
    return passed;
}
