/*
 * default_hasher.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "default_hasher.h"


unsigned long DefaultHasher::hash(const std::string& id)
{
    return std::hash<std::string>{}(id);
}
