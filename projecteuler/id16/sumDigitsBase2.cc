//******************************************************************
// File: sumDigitsBase2.cc
//
// Author: Randy Obringer
// Email: ro120908@ohio.edu
//
// Problem: Find the sum of the digits of 2^1000
//
// Last Updated: 07/01/2011
//******************************************************************

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

string convertIntString(int n){ //convert integers to strings
  ostringstream out;
  out << n;
  return out.str();
}

int main(){
  string number="2"; //base 2
  string stempdigit,stempcarry,stempnumber,stempnumber2="";
  int itemp;
  int carry=0;
  int digit=0;
  for(int i=1;i<1000;i++){ //bound is the power
    carry=0;
    stempnumber=stempnumber2="";
    for(int j=number.length()-1;j>=0;j--){ //produce each multiplication of 2
      stempnumber=stempnumber2;
      itemp=((number[j]-'0')*2)+carry;
      digit=itemp%10;
      carry=itemp/10;
      stempdigit=convertIntString(digit);
      stempcarry=convertIntString(carry);
      stempnumber2=stempdigit+stempnumber;
      if((j==0)&&(carry>0)){
        stempnumber=stempcarry+stempnumber2;
        stempnumber2=stempnumber;
      }
    }
    number=stempnumber2;
  }
  int sum=0;
  for(int i=0;i<number.length();i++){ //count sum of digits
    sum+=(number[i]-'0');
  }
  cout << "2^1000 = " << number << endl;
  cout << "sum of digits: " << sum << endl;
}

