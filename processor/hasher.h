/*
 * hasher.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef HASHER_H
#define HASHER_H

class Hasher
{
public:
    virtual unsigned long hash(const string& id);
};

#endif /* !HASHER_H */
