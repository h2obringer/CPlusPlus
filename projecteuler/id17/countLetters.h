//******************************************************************
//  File: countLetters.h
//
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Description: Class declaration
//
//  Last Updated: 6/18/2011
//******************************************************************

#ifndef COUNTLETTERS_H
#define COUNTLETTERS_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class countLetters{
  public:
    string numberToWord(int n);
    int count(string &word);
    long long findAnswer();
};

#endif
