/*
 * log.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "log.h"


void initLog(const std::string& ps)
{
    makeDir((ps + "_log/").c_str());
    FLAGS_log_dir = (ps + "_log/");
    google::InitGoogleLogging(ps.c_str());
    LOG(INFO) << "GLOG INITIALIZED";
}
