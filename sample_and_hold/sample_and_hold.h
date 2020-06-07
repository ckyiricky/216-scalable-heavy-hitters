#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <cassert>
#include <thread>
#include <unordered_map> 
#include <algorithm>    // std::sort
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

// Struct for the Oscars dataset
class Oscar {
private:
	string category;
	string name;
	string film;
	string winner;

  // Helper function splitting string by ','
  vector<string> getList(string s){
    vector<string> l = {};

    size_t pos = 0;
    std:string token;
    while ((pos = s.find(", ")) != std::string::npos) {
      token = s.substr(0, pos);
      l.push_back(token);
      s.erase(0, pos + 2);
    }
    if (s.length() > 0)
      l.push_back(s);
    return l;
  }  

public:
  Oscar(string s){
    vector<string> l = getList(s);
    assert(l.size() >= 4);

    category = l[0];
    name = l[1];
    film = l[2];
    winner = l[3];
  }

  string show() {
    string s = "";
    s.append(category + ", ");
    s.append(name + ", ");
    s.append(film + ", ");
    s.append(winner);
    return s;    
  }

  string getCategory() {
    return category;
  }
};


// thread-safe queue
template <typename T>
class SafeQueue
{
 public:
 
  T pop()
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    auto item = queue_.front();
    queue_.pop();
    return item;
  }
 
  void pop(T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    item = queue_.front();
    queue_.pop();
  }
 
  void push(const T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
  }
 
  void push(T&& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(std::move(item));
    mlock.unlock();
    cond_.notify_one();
  }
 
 private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
};

#endif