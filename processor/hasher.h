/*
 * hasher.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef HASHER_H
#define HASHER_H

#include <string>

class Hasher
{
public:
    virtual unsigned long hash(const std::string& id) = 0;
};

#endif /* !HASHER_H */
