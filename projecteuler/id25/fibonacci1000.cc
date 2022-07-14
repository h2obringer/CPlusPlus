//******************************************************************
// File: fibonacci1000.cc
//
// Author: Randy Obringer
// Email: ro120908@ohio.edu
//
// Problem: What is the first term in the fibonacci sequence to contain
//   1000 digits? 
//
// Given: The fibonacci sequence is defined by the recurrence relation:
//   Fn=Fn-1 + Fn-2, where F1=1 and F2=1.
//   Hence F3=2, F4=3, F5=5, F6=8, F7=13, F8=21, F9=34, F10=55,
//   F11=89, and F12=144. 
//
// Answer: The 4782nd term contains 1000 digits.
//
// Last Updated: 07/04/2011
//*******************************************************************


#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int abs(int n){
  if(n>=0){
    return n;
  }else{
    return n*(-1);
  }
}

string itos(int n){
  ostringstream out;
  out << n;
  return out.str();
}

int main(){
  int itemp;
  int term=2; //term in the fibonnaci sequence
  int difference; //difference in the length of the 2 terms (current and next).
  int l1; //length of current
  int l2; //length of next
  string stemp,stemp2;
  string current="1"; //Fn-1
  int carry;
  int digit;
  string scarry;
  string sdigit;
  string next="1"; //Fn
  do{
    carry=0;
    l1=current.length();                  //formatting strings for addition
    l2=next.length();                     //
    difference=abs(l1-l2);                //
    if(difference>0){                     //
      for(int i=0;i<difference;i++){      // (adding zeros to the front of
        current="0"+current;              // the shorter string so they can
      }                                   // be added together)
    }                                     //formatting strings for addition
    
    stemp=stemp2="";
    for(int j=next.length()-1;j>=0;j--){ 
      itemp=(next[j]-'0')+(current[j]-'0')+carry;
      digit=itemp%10;
      carry=itemp/10;
      sdigit=itos(digit);
      stemp=sdigit+stemp;
      if((j==0)&&(carry>0)){
        scarry=itos(carry);
        stemp=scarry+stemp;
      }
    }
    current=next;
    next=stemp;
    term++;
  }while(next.length()<1000);
  cout << "F" << term << " = " << next << endl;
}
