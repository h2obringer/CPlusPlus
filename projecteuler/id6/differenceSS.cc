//*****************************************************************
//  File: differenceSS.cc
//  
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Description: Class implementation
//
//  Last Updated: 6/16/2011
//
//*****************************************************************
#include "differenceSS.h"

//*****************************************************************
//  Function: sumOfSquares (public)
//  
//  Parameter: an integer. Will be the bound of the numbers
//  
//  Effect: Computes the sum of the squares of the first n numbers
//
//*****************************************************************
long long differenceSS::sumOfSquares(int n){
  long long sum=0;
  for(long long i=1;i<=n;i++){
    sum+=(i*i);
  }
  return sum;
}

//*****************************************************************
//  Function: squareOfSum (public)
//  
//  Paramter: an integer. Will be the bound of the numbers
//
//  Effect: Computes the square of the sum of the first n numbers
//
//******************************************************************
long long differenceSS::squareOfSums(int n){
  long long sum=0;
  for(long long i=1;i<=n;i++){
    sum+=i;
  }
  long long squared=sum*sum;
  return squared;
}
