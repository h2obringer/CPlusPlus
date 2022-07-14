//*****************************************************************
//  File: main.cc
//  
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Problem: Find the largest palindrome made from the product of
//    two 3-digit numbers
//
//  Last Updated: 6/16/2011
//
//*****************************************************************
#include "digitPalindrome.h"

int main(){
  digitPalindrome dp;
  int highest3digitProduct=dp.product();
  cout << highest3digitProduct << endl;
}
