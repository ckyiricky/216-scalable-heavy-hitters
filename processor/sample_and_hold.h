/*
 * sample_and_hold.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SAMPLE_AND_HOLD_H
#define SAMPLE_AND_HOLD_H

#include <string>
#include <unordered_map>
#include "filter.h"

class SampleAndHold : public Filter
{
private:
    unsigned long mThreshold;
    double mProbability;
    std::unordered_map<std::string, unsigned long> mStat;
public:
    SampleAndHold() = delete;
    SampleAndHold(unsigned long);
    SampleAndHold(unsigned long, double);
    void setThreshold(unsigned long t){mThreshold = t;};
    void setProbability(double p){mProbability = p;};
    bool filter(std::shared_ptr<Data>);
};

#endif /* !SAMPLE_AND_HOLD_H */
