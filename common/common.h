/*
 * common.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

/*
 * This class is for tvshows dataset, one object represents one piece of data
 * TODO: review member of the class
 * TODO: review UID creation, should that be enough to uniquely identify one data piece
 * TODO: move constructor
 *
 * TODO: Unit test
 * TODO: Log system
 */

#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <unordered_map>
using namespace std;

/*
 * Class of tv_show data,
 * Not thread safe.
 */
class TVShows
{
private:
    string mUID;
    string mTitle;
    string mDirector;
    int mReleaseYear;
    /*
     * Store additional information of the tvshows
     */
    unordered_map<string, string> mExtra;
    /*
     * Might need to update this function:
     * 1. is current one enough to uniquely identify a piece of data?
     * 2. is this format UID easy to use --  int or uuid better?
     * 3. is encryption needed for the id?
     */
    string createUID() const;
public:
    TVShows(const string& title, const string& director, int year, const unordered_map<string, string>& extraInfo);
    TVShows(const string& title, const string& director, int year);
    const string& getUID() const {return mUID;}
    const string& getTitle() const {return mTitle;}
    int getReleaseYear() {return mReleaseYear;}
    const unordered_map<string, string>& getExtraInfo() const {return mExtra;}
    void setTitle(const string&);
    void setDirector(const string&);
    void setReleaseYear(int);
    void setExtraInfo(const unordered_map<string, string>&);
    void setExtraInfo(const string& key, const string& value);
    bool isEqual(const TVShows& other) {return this->mUID == other.getUID();}
};

#endif /* !COMMON_H */
