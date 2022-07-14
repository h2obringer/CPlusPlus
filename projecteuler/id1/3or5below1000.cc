//*****************************************************************
//  File: 3or5below1000.cc
//  
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Problem: Find the sum of the multiples of 3 or 5 below 1000
//
//  Last Updated: 6/12/2011
//
//*****************************************************************

#include <iostream>
using namespace std;

int main(){
  int sum=0;
  for(int i=0;i<1000;i++){
    if((i%3==0)||(i%5==0)){
      sum+=i;
    }
  }
  cout << endl;
  cout << sum << endl;
}
