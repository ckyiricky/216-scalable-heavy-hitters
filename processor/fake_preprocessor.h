/*
 * fake_preprocessor.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef FAKE_PREPROCESSOR_H
#define FAKE_PREPROCESSOR_H

#include "data_preprocessor.h"

class FakePreprocessor : public DataPreprocessor
{
public:
    shared_ptr<TVShows> preprocess()
    {
        return make_shared<TVShows>("testtitle", "rick", 1995);
    }
    ~FakePreprocessor(){}
};

#endif /* !FAKE_PREPROCESSOR_H */
