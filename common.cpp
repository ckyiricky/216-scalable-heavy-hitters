/*
 * common.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "common.h"


TVShows::TVShows(const string& title, const string& director, int year)
    : TVShows(title, director, year, unordered_map<string, string>())
{
}

TVShows::TVShows(const string& title, const string& director, int year, const unordered_map<string, string>& extraInfo)
    : mTitle(title), mDirector(director), mReleaseYear(year), mExtra(extraInfo)
{
    mUID = createUID();
}

void TVShows::setTitle(const string& newTitle)
{
    if (all_of(newTitle.begin(), newTitle.end(), isspace))
    {
        printf("Set title to empty string, set failed");
        return;
    }
    mTitle = newTitle;
}

void TVShows::setDirector(const string& newDirector)
{
    if (all_of(newDirector.begin(), newDirector.end(), isspace))
    {
        printf("Set director to empty string, set failed");
        return;
    }
    mDirector = newDirector;
}

void TVShows::setReleaseYear(int year)
{
    mReleaseYear = year;
}

void TVShows::setExtraInfo(const unordered_map<string, string>& extra)
{
    mExtra = extra;
}

void TVShows::setExtraInfo(const string& key, const string& value)
{
    if (all_of(key.begin(), key.end(), isspace))
    {
        printf("Extra info cant add empty key");
        return;
    }
    mExtra[key] = value;
}

string TVShows::createUID() const
{
    return mTitle + "###***" + mDirector + "###***" + to_string(mReleaseYear);
}
