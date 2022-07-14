//******************************************************************
//
//  File: greatestProduct.cc
//  
//  Author: RandyObringer
//  Email: ro120908@ohio.edu
//
//  Description: Class implementation
//
//  Last Updated: 6/16/2011
//
//******************************************************************

#include "greatestProduct.h"
//******************************************************************
//  Function: findGreatest (public)
//  Parameter: a vector of strings, this will be the 1000-digit
//    number just split up to make manageable
//  Effect: finds the highest product of 5 consecutive digits
//    in the 1000-digit number
//******************************************************************
int greatestProduct::findGreatest(vector<string> &v){
  int one=0;
  int two=1;
  int three=2;
  int four=3;
  int five=4;
  int runo,rdos,rtres,rquatro,rcinco,cuno,cdos,ctres,cquatro,ccinco=0;
  int max,temp,num1,num2,num3,num4,num5=0;
  while(five<1000){ 
    runo=one/50;
    cuno=one%50;
    rdos=two/50;
    cdos=two%50;
    rtres=three/50;
    ctres=three%50;
    rquatro=four/50;
    cquatro=four%50;
    rcinco=five/50;
    ccinco=five%50;
    num1=(v[runo][cuno]-'0');
    num2=(v[rdos][cdos]-'0');
    num3=(v[rtres][ctres]-'0');
    num4=(v[rquatro][cquatro]-'0');
    num5=(v[rcinco][ccinco]-'0');
    temp=num1*num2*num3*num4*num5;
    if(temp>=max){
      max=temp;
    }
    ++one;
    ++two;
    ++three;
    ++four;
    ++five;
  }
  return max;
}
