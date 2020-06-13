/*
 * data_preprocessor_impl.h
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef DATA_PREPROCESSOR_IMPL_H
#define DATA_PREPROCESSOR_IMPL_H

#include "data_preprocessor.h"

class DataPreprocessorImpl : public DataPreprocessor
{
private:
    std::vector<std::string> mDataCategories;
    std::vector<int> mUID;
    int mDataSize;
    // Helper function splitting string by ','
    void getList(std::string& s, std::vector<std::string>& out);
public:
    void setCategories(std::vector<std::string>& c){mDataCategories = c;}
    void setSize(int size){mDataSize = size;}
    void setIDKeys(std::vector<int>&& keys){mUID = keys;}
    // Function to turn a string into an data object
    std::shared_ptr<Data> preprocess(std::string&);
    std::shared_ptr<Data> preprocess(){return nullptr;};
    void init(void**);
    // print data function
    std::string getData(std::shared_ptr<Data>);
};

#endif /* !DATA_PREPROCESSOR_IMPL_H */
