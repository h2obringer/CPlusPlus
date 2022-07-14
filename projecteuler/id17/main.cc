//******************************************************************
//  File: main.cc
//
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Problem: If all the numbers from 1 to 1000 inclusive were written 
//    out in words, how many letters would be used?
//  
//  Answer: 21124
//
//  Last Updated: 6/18/2011
//******************************************************************

#include "countLetters.h"

int main(){
  countLetters cl;
  long long total=cl.findAnswer();
  cout << total << endl;
}
