/*
 * data_preprocessor_impl.cpp
 * Copyright (C) 2020 rick <ckyiricky@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "data_preprocessor_impl.h"

using namespace std;

void DataPreprocessorImpl::getList(std::string& s, std::vector<std::string>& out)
{
	size_t pos = 0;
	while ((pos = s.find(", ")) != string::npos)
    {
		string token = s.substr(0, pos);
		out.push_back(move(token));
		s.erase(0, pos + 2);
	}
	if (s.length() > 0)
		out.push_back(s);
}

std::shared_ptr<Data> DataPreprocessorImpl::preprocess(string& s)
{
	shared_ptr<Data> data = make_shared<Data>();
    vector<string> strs;
    getList(s, strs);

	if(strs.size() > 0)
    {
		data->data = move(strs);
		data->categories = mDataCategories;
		data->size = mDataSize;
	}
	
	// set UID to values in vUID global vector
	string id;
	for (int i : mUID)
    {
		if (i < data->data.size())
        {
			id += data->data[i] + ", ";
		}
	}
	data->UID = id.substr(0, id.size() - 2);
    return data;
}

string DataPreprocessorImpl::getData(std::shared_ptr<Data> data)
{
	string s;
	for (string& t : data->data)
    {
		s.append(t + ", ");
	}
	return data->UID + ": " + s.substr(0, s.size() - 2);
}

void DataPreprocessorImpl::init(void** attributes)
{
    mDataSize = *(int*)attributes[0];
    mDataCategories = *(vector<string>*)attributes[1];
    mUID = *(vector<int>*)attributes[2];
}
