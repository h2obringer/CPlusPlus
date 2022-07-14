//*****************************************************************
//  File: main.cc
//  
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Problem: Find the difference between the sum of the squares of 
//    the first 100 natural numbers and the square of the sum
//
//  Last Updated: 6/16/2011
//
//*****************************************************************
#include "differenceSS.h"

int main(){
  differenceSS ss;
  long long difference=ss.squareOfSum(100)-ss.sumOfSquares(100);
  cout << difference << endl;
}
