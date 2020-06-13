/*
 * data_preprocessor.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

/*
 * TODO: design this class
 *      for now its just for test use
 */

#ifndef DATA_PREPROCESSOR_H
#define DATA_PREPROCESSOR_H

#include <memory>
#include "data.h"

class DataPreprocessor
{
public:
    virtual void init(void**) = 0;
    virtual std::shared_ptr<Data> preprocess() = 0;
    virtual std::shared_ptr<Data> preprocess(std::string&) = 0;
};

#endif /* !DATA_PREPROCESSOR_H */
