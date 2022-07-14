//*****************************************************************
//  File: digitPalindrome.cc
//  
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Description: Class implementation
//
//  Last Updated: 6/16/2011
//
//*****************************************************************

#include "digitPalindrome.h"
//*****************************************************************
//  Function: product (public)
//
//  Function calls: isPalindrome
//  Effect: checks all possible products of two 3-digit numbers
//    and returns the highest number that is a palindrome
//*****************************************************************
int digitPalindrome::product(){
  int max=0;
  int temp=0;
  for(int i=100;i<1000;i++){
    for(int j=100;j<1000;j++){
      temp=i*j;
      if((isPalindrome(temp)==true)&&(temp>=max)){
        max=temp;
      }
    }
  }
  return max;
}

//*****************************************************************
//  Function: convertIntString (private)
//  
//  Paramter: an integer
//  Effect: convert an integer to a string and returns the string
//*****************************************************************
string digitPalindrome::convertIntString(int n){
  ostringstream out;
  out << n;
  return out.str();
}

//*****************************************************************
//  Function: isPalindrome (private)
//
//  Parameter: an integer
//  Effect: Checks if the number is a palindrome or not
//*****************************************************************
bool digitPalindrome::isPalindrome(int n){
  string number=convertIntString(n);
  int numberLength=number.length();
  bool palin=true;
  for(int i=0;i<numberLength;i++){
    if(number[i]!=number[numberLength-i-1]){
      palin=false;
      break;
    }
  }
  return palin;
}
