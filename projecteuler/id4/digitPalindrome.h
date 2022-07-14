//*****************************************************************
//  File: digitPalindrome.h
//  
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Description: class declaration
//  Last Updated: 6/16/2011
//
//*****************************************************************
#ifndef DIGITPALINDROME_H
#define DIGITPALINDROME_H
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class digitPalindrome{
  public:
    int product();
  private:
    bool isPalindrome(int n); 
    string convertIntString(int n);
};

#endif
