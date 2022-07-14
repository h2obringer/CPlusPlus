//******************************************************************
// File: sundays.cc
//
// Author: Randy Obringer
// Email: ro120908@ohio.edu
//
// Problem: How many sundays fall on the first of the month in the
// 20th century? (1 january 1901 to 31 december 2000)
//
// Answer: 171
// 
// Given:
//   1 jan 1900 was a monday
//   30 days in september, april, june, and november
//   31 days for the rest of the months
//   28 for january except on leap years. (then theres 29)
//   7 days a week
//
// Last Updated: 07/02/2011
//******************************************************************


#include <iostream>
#include <cstdlib>
using namespace std;

//****************************
// monday = 0;
// tuesday = 1;
// wednesday = 2;
// thursday = 3;
// friday = 4;
// saturday = 5;
// sunday = 6;
//****************************


int main(){
  long long days=-1; //makes days%7 = 0 as monday when days++ on start of loop
  long long sundaysOnFirst=0;
  int year=1900;
  for(int year=1900;year<2001;year++){
    for(int jan=1;jan<=31;jan++){ //month 1
      days++;
      if((days%7==6)&&(jan==1)&&(year!=1900)) sundaysOnFirst++;
    }
    if(((year%100==0)&&(year%400==0))||((year%100!=0)&&(year%4==0))){ //leap year
      for(int feb=1;feb<=29;feb++){ //month 2
        days++;
        if((days%7==6)&&(feb==1)&&(year!=1900)) sundaysOnFirst++;
      }
    }else{ //not a leap year
      for(int feb=1;feb<=28;feb++){ //month 2
        days++;
        if((days%7==6)&&(feb==1)&&(year!=1900)) sundaysOnFirst++;
      }
    }
    for(int mar=1;mar<=31;mar++){ //month 3
      days++;
      if((days%7==6)&&(mar==1)&&(year!=1900)) sundaysOnFirst++;
    }
    for(int apr=1;apr<=30;apr++){ //month 4
      days++;
      if((days%7==6)&&(apr==1)&&(year!=1900)) sundaysOnFirst++;
    }
    for(int may=1;may<=31;may++){ //month 5
      days++;
      if((days%7==6)&&(may==1)&&(year!=1900)) sundaysOnFirst++;
    }
    for(int june=1;june<=30;june++){ //month 6
      days++;
      if((days%7==6)&&(june==1)&&(year!=1900)) sundaysOnFirst++;
    }
    for(int july=1;july<=31;july++){ //month 7
      days++;
      if((days%7==6)&&(july==1)&&(year!=1900)) sundaysOnFirst++;
    }
    for(int aug=1;aug<=31;aug++){ //month 8
      days++;
      if((days%7==6)&&(aug==1)&&(year!=1900)) sundaysOnFirst++;
    }
    for(int sept=1;sept<=30;sept++){ //month 9
      days++;
      if((days%7==6)&&(sept==1)&&(year!=1900)) sundaysOnFirst++;
    }
    for(int oct=1;oct<=31;oct++){ //month 10
      days++;
      if((days%7==6)&&(oct==1)&&(year!=1900)) sundaysOnFirst++;
    }
    for(int nov=1;nov<=30;nov++){ //month 11
      days++;
      if((days%7==6)&&(nov==1)&&(year!=1900)) sundaysOnFirst++;
    }
    for(int dec=1;dec<=31;dec++){ //month 12
      days++;
      if((days%7==6)&&(dec==1)&&(year!=1900)) sundaysOnFirst++;
    }
  }
  cout << "The number of sundays that fell" << endl;
  cout << "on the first of the month during" << endl;
  cout << "the twentieth century: " << sundaysOnFirst << endl;
}
