//******************************************************************
//  File: sequence.cc
//
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Problem: If n is even n/2, if n is odd 3n+1. Which starting
//    number under one million produces the longest chain?
//
//  Answer: 837799
//
//  Last Updated: 6/17/2011
//******************************************************************
#include <iostream>
using namespace std;

int main(){
  long long longestSequence=0;
  long long currentSequence=0;
  int largest=0;
  long long start;
  long long belowAmillion=999999; //Actual start number for a sequence
  while(belowAmillion>0){
    start=belowAmillion;
    //cout << "start: " << start << endl;
    currentSequence=1;
    while(start!=1){
      if(start%2==0){
        start=start/2;
      }else{
        start=(3*start)+1;
      }
      currentSequence++;
    }
    if(currentSequence>=longestSequence){
      longestSequence=currentSequence;
      largest=belowAmillion;
    }
    //cout << "currentSequence: " << currentSequence << endl;
    belowAmillion--;
  }
  cout << largest << endl;
}
