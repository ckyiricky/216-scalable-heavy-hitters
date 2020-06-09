/*
 * default_hasher.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef DEFAULT_HASHER_H
#define DEFAULT_HASHER_H

#include "hasher.h"

class DefaultHasher : public Hasher
{
public:
    unsigned long hash(const std::string& id);
    ~DefaultHasher(){}
};

#endif /* !DEFAULT_HASHER_H */
