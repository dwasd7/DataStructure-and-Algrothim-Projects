
#ifndef _WORDENTRY_H_
#define _WORDENTRY_H_

#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

struct wordEntry {
  string word;
  int count;
  list<int> numlist;
  int lastline;

  string Key() const;
};

#endif