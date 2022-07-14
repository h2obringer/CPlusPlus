//******************************************************************
//  File: pythagoreanTriplets.cc
//  
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Problem: There exists one pythagorean triplet in which a+b+c=1000
//    Find the product of a, b, and c
//
//  Answer: 31875000
//
//  Last Updated: 6/16/2011
//
//******************************************************************

#include <iostream>
using namespace std;

int main(){
  int as,bs,cs,sum;
  long long product=0;
  for(int a=1;a<500;a++){
    for(int b=1;b<1000;b++){
      for(int c=1;c<1000;c++){
        as=a*a;
        bs=b*b;
        cs=c*c;
        sum=a+b+c;
        if((as+bs==cs)&&(a<b)&&(b<c)&&(sum==1000)){
          product=a*b*c;
          break;
        }        
      }
    }
  }
  cout << product << endl;
}
