//**************************************************************************************
//File: main.cc
//
//Author: Randal Obringer
//
//Date Last Modified: ~2011
//
//Desciption: Use brute force method to compute hash values for the strings A-ZZZZZZZ.
//	Print the totals of which strings got which values. Very slow. Used to demonstrate the
//	need for better hashing.
//**************************************************************************************

#include "length7.h"

int main(){
  length7 E;
  E.compute();
  long long a=E.get0();
  long long b=E.get996();
  long long c=E.get500();
  long long d=E.get400();
  long long e=E.get211();
  long long t=E.getTotal();

  cout << "0: " << a << "/" << t << endl;
  cout << "996: " << b << "/" << t << endl;
  cout << "500: " << c << "/" << t << endl;
  cout << "400: " << d << "/" << t << endl;
  cout << "211: " << e << "/" << t << endl;
}
