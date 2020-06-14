/*
 * sample_and_hold.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <cstdlib>
#include <ctime>
#include "log.h"
#include "sample_and_hold.h"

using namespace std;

SampleAndHold::SampleAndHold(unsigned long t)
    : mThreshold(t)
{
    LOG(INFO) << "Set sample probability to default value: 0.3";
    mProbability = 0.3;
    srand(time(nullptr));
}

SampleAndHold::SampleAndHold(unsigned long t, double p)
    : mThreshold(t)
{
    if (p <= 0 || p > 1.0)
    {
        LOG(WARNING) << "Input sample probability illegal (<=0 or >1), set to default value 0.3";
        mProbability = 0.3;
    }
    mProbability = p;
    srand(time(nullptr));
}

bool SampleAndHold::filter(shared_ptr<Data> data)
{
    if (mStat.count(data->UID))
    {
        if (++mStat[data->UID] >= mThreshold)
            return true;
        return false;
    }
    if (rand() % 1000 < 1000 * mProbability)
    {
        mStat[data->UID] = 1;
        if (mStat[data->UID] >= mThreshold)
            return true;
    }
    return false;
}
