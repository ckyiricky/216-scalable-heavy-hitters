/*
 * common.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <algorithm>
#include "log.h"
#include "common.h"


TVShows::TVShows(const std::string& title, const std::string& director, int year)
    : TVShows(title, director, year, std::unordered_map<std::string, std::string>())
{
}

TVShows::TVShows(const std::string& title, const std::string& director, int year, const std::unordered_map<std::string, std::string>& extraInfo)
    : mTitle(title), mDirector(director), mReleaseYear(year), mExtra(extraInfo)
{
    mUID = createUID();
}

void TVShows::setTitle(const std::string& newTitle)
{
    if (std::all_of(newTitle.begin(), newTitle.end(), isspace))
    {
        LOG(ERROR) << "Set title to empty std::string, set failed";
        return;
    }
    mTitle = newTitle;
}

void TVShows::setDirector(const std::string& newDirector)
{
    if (std::all_of(newDirector.begin(), newDirector.end(), isspace))
    {
        LOG(ERROR) << "Set director to empty std::string, set failed";
        return;
    }
    mDirector = newDirector;
}

void TVShows::setReleaseYear(int year)
{
    mReleaseYear = year;
}

void TVShows::setExtraInfo(const std::unordered_map<std::string, std::string>& extra)
{
    mExtra = extra;
}

void TVShows::setExtraInfo(const std::string& key, const std::string& value)
{
    if (std::all_of(key.begin(), key.end(), isspace))
    {
        LOG(ERROR) << "Extra info cant add empty key";
        return;
    }
    mExtra[key] = value;
}

std::string TVShows::createUID() const
{
    return mTitle + "###***" + mDirector + "###***" + std::to_string(mReleaseYear);
}
