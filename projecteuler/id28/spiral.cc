//******************************************************************
// File: spiral.cc
//
// Author: Randy Obringer
// Email: ro120908@ohio.edu
//
// Problem: Find the sum of the diagonals formed by a 1001x1001 square
//   starting with 1 in the center and moving in a clockwise motion.
//   Ex: 
//
//  21 22 23 24 25
//  20  7  8  9 10
//  19  6  1  2 11
//  18  5  4  3 12
//  17 16 15 14 13
//
// Answer: 33529407555864
// Answer: 669171002
//
// Last Updated: 07/09/2011
//******************************************************************

#include <set>
#include <iostream>
using namespace std;

int main(){
  set<long long int> diagonal1;
  set<long long int> diagonal2;
  long long int sum=0;
  long long int temp=0;
  long long int max=1001*1001;
  for(int i=1;i<=1001;i++){ //1001 by 1001
    if(i%2!=0){ //odd
      temp=i*i; //formula for #'s going up/right from start
      diagonal1.insert(temp);
      temp=temp-(i-1); //formula for #'s going up/left from start
      diagonal2.insert(temp);
    }
    if(i%2==0){ //even
      temp=(i*i)+1; //formula for #'s going down/left from start
      diagonal1.insert(temp);
      temp=temp-i; //formula for #'s going down/right from start
      diagonal2.insert(temp);
    }          //diagonal from top right to bottow left is now covered.
  }
  set<long long int>::iterator it;
  for(it=diagonal1.begin();it!=diagonal1.end();++it){ //add the sum
    sum+=(*it);
  }
  for(it=diagonal2.begin();it!=diagonal2.end();++it){ //add the sum
    sum+=(*it);
  }
  cout << "sum: " << sum << endl; //answer
}

