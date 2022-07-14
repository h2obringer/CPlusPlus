//******************************************************************
// File: factorial.cc
// 
// Author: Randy Obringer
// Email: ro120908@ohio.edu
//
// Problem: Find the sum of the digits of 100!
// 
// Answer: 648
//
// Last Updated: 07/03/2011
//*******************************************************************

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

string convertIntString(int n){
  ostringstream out;
  out << n;
  return out.str();
}

int main(){
  string number="100"; //base 2
  string stempdigit,stempcarry,stempnumber,stempnumber2="";
  string tempdigit,tempcarry,tempnumber,tempnumber2="";
  int itemp;
  int carry=0;
  int digit=0;
  int first,second=0;
  for(int i=99;i>=2;i--){ //bound is the power
    carry=0;
    stempnumber=stempnumber2=tempnumber=tempnumber2="";
    for(int j=number.length()-1;j>=0;j--){ //
      stempnumber=stempnumber2;
      first=i%10;
      itemp=((number[j]-'0')*first)+carry;
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
    //number=stempnumber2; //this is the first digit multiplied by the current number
    carry=0;
    tempnumber2="0";
    for(int j=number.length()-1;j>=0;j--){ //
      tempnumber=tempnumber2;
      second=i/10;
      itemp=((number[j]-'0')*second)+carry;
      digit=itemp%10;
      carry=itemp/10;
      tempdigit=convertIntString(digit);
      tempcarry=convertIntString(carry);
      tempnumber2=tempdigit+tempnumber;
      if((j==0)&&(carry>0)){
        tempnumber=tempcarry+tempnumber2;
        tempnumber2=tempnumber;
      }
    }
    //all that is left is to add the 2 numbers together
    int l1=stempnumber2.length();
    int l2=tempnumber2.length();
    int difference=l2-l1;
    string temp;
    for(int j=0;j<difference;j++){
      temp="0"+stempnumber2;
      stempnumber2=temp;
    } //makes both strings the same length
    carry=0;
    tempnumber="";
    for(int j=l2-1;j>=0;j--){
      l1=(stempnumber2[j]-'0');
      l2=(tempnumber2[j]-'0');
      itemp=l1+l2+carry;
      digit=itemp%10;
      carry=itemp/10;
      tempdigit=convertIntString(digit);
      if(tempnumber==""){
        number=tempdigit;
      }else{
        number=tempdigit+tempnumber;
      }
      tempnumber=number;
      if((j==0)&&(carry>0)){
        tempcarry=convertIntString(carry);
        number=tempcarry+tempnumber;
      }
    } 
  }
  while((number[0]-'0')==0){
    number.erase(0,1);
  }
  cout << "100! = " << number << endl;
  int sum=0;
  for(int i=0;i<number.length();i++){
    sum+=(number[i]-'0');
  }
  cout << "sum of digits: " << sum << endl;
}
