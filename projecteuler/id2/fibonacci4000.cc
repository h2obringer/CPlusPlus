//*************************************************************
//  File: fibonacci4000.cc
//
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Problem: By considering the terms in the fibonacci sequence
//    whose values do not exceed four million. Find the sum of 
//    the even-valued terms.
//
//  Last Updated: 6/12/2011
//
//*************************************************************

#include <iostream>
using namespace std;

int main(){
  int first=1;
  int second=1;
  int next=0;
  int sum=0;
  while(second<4000000){
    next=first+second;
    first=second;
    second=next;
    if((second%2==0)&&(second<4000000)){
      sum+=second;
    }
  }
  cout << sum << endl;
}
