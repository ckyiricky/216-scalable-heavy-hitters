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

#include <string>
#include <glog/logging.h>

void initLog(const std::string& ps);

#endif /* !LOG_H */
