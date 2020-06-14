/*
 * net_flow.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef NET_FLOW_H
#define NET_FLOW_H

#include <string>
#include <unordered_map>
#include "filter.h"

class NetFlow : public Filter
{
private:
    unsigned long mThreshold;
    double mProbability;
    std::unordered_map<std::string, unsigned long> mStat;
public:
    NetFlow() = delete;
    NetFlow(unsigned long);
    NetFlow(unsigned long, double);
    void setThreshold(unsigned long t){mThreshold = t;};
    void setProbability(double p){mProbability = p;};
    bool filter(std::shared_ptr<Data>);
};

#endif /* !NET_FLOW_H */
