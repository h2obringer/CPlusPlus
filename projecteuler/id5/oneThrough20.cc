//*****************************************************************
//  File:oneThrough20.cc
//  
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Problem: What is the smallest positive number evenly divisible
//    by all of the numbers from 1 to 20?
//  Given: 2520 is the smallest number evenly divisible by all the
//    numbers 1 to 10
//
//  Last Updated: 6/16/2011
//
//*****************************************************************

#include <iostream>
using namespace std;

int main(){
  bool allDivisible=false;
  long long i=2521; //has to be bigger than 2520
  
  while(allDivisible==false){
    if((i%20==0)&&(i%19==0)&&(i%18==0)&&(i%17==0)&&(i%16==0)&&(i%15==0)&&(i%14==0)
      &&(i%13==0)&&(i%12==0)&&(i%11==0)&&(i%10==0)&&(i%9==0)&&(i%8==0)&&(i%7==0)
      &&(i%6==0)&&(i%5==0)&&(i%4==0)&&(i%3==0)&&(i%2==0)){
      allDivisible=true;
    }else{
      i++;
    }
  }
  cout << i << endl;
}
