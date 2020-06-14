/*
 * net_flow.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <cstdlib>
#include <ctime>
#include "net_flow.h"
#include "log.h"

using namespace std;

NetFlow::NetFlow(unsigned long t)
    : mThreshold(t)
{
    LOG(INFO) << "Set sample probability to default value: 0.3";
    mProbability = 0.3;
    srand(time(nullptr));
}

NetFlow::NetFlow(unsigned long t, double p)
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

bool NetFlow::filter(shared_ptr<Data> data)
{
    if (rand() % 1000 < 1000 * mProbability)
    {
        if (++mStat[data->UID] >= mThreshold)
            return true;
    }
    return false;
}
