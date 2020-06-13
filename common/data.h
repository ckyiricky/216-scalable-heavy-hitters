/*
 * data.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>

struct Data
{
    std::vector<std::string> data;
    std::vector<std::string> categories;
	int size;
    std::string UID;
};

#endif /* !DATA_H */
