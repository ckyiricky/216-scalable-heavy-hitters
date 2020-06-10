/*
 * log.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef LOG_H
#define LOG_H

#ifdef _WIN32
#include <direct.h>
#define getCurrentDir _getcwd
#define makeDir _mkdir
#else
#include <sys/stat.h>
#include <sys/types.h>
#define getCurrentDir getcwd
#define makeDir(dir) mkdir(dir, 0755)
#endif

#include <glog/logging.h>
#include <string>

void initLog(const std::string& ps)
{
    makeDir((ps + "_log/").c_str());
    FLAGS_log_dir = (ps + "_log/");
    google::InitGoogleLogging(ps.c_str());
    LOG(INFO) << "GLOG INITIALIZED";
}

#endif /* !LOG_H */
