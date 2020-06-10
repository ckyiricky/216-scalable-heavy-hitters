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

/*
 * Class of tv_show data,
 * Not thread safe.
 */
class TVShows
{
private:
    std::string mUID;
    std::string mTitle;
    std::string mDirector;
    int mReleaseYear;
    /*
     * Store additional information of the tvshows
     */
    std::unordered_map<std::string, std::string> mExtra;
    /*
     * Might need to update this function:
     * 1. is current one enough to uniquely identify a piece of data?
     * 2. is this format UID easy to use --  int or uuid better?
     * 3. is encryption needed for the id?
     */
    std::string createUID() const;
public:
    TVShows(const std::string& title, const std::string& director, int year, const std::unordered_map<std::string, std::string>& extraInfo);
    TVShows(const std::string& title, const std::string& director, int year);
    const std::string& getUID() const {return mUID;}
    const std::string& getTitle() const {return mTitle;}
    int getReleaseYear() {return mReleaseYear;}
    const std::unordered_map<std::string, std::string>& getExtraInfo() const {return mExtra;}
    void setTitle(const std::string&);
    void setDirector(const std::string&);
    void setReleaseYear(int);
    void setExtraInfo(const std::unordered_map<std::string, std::string>&);
    void setExtraInfo(const std::string& key, const std::string& value);
    bool isEqual(const TVShows& other) {return this->mUID == other.getUID();}
};

#endif /* !COMMON_H */
