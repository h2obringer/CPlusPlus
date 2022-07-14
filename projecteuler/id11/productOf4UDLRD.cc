//******************************************************************
// File: productOf4UDLRD.cc
//
// Author: Randy Obringer
// Email: ro120908@ohio.edu
//
// Problem: Find the largest product of 4 consecutive numbers in the 
//   table below. (left/right/up/down/diagonally)
//
// Answer: 70600674
//
// Last Updated: 07/01/2011
//******************************************************************
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;

void tableStringToTableInt(vector<string> &s,vector<int> &t){
  for(int i=0;i<s.size();i++){
    istringstream in(s[i]);
    while(in){ 
      int n;
      in >> n;
      t.push_back(n);
    }
    t.pop_back();
  }
}

int main(){
  vector<string> table; //store as strings for easier input of numbers and easier reading
  table.push_back("08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08"); //length 59, 20 spaces
  table.push_back("49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00");
  table.push_back("81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65");
  table.push_back("52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91");
  table.push_back("22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80");
  table.push_back("24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50");
  table.push_back("32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70");
  table.push_back("67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21");
  table.push_back("24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72");
  table.push_back("21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95");
  table.push_back("78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92");
  table.push_back("16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57");
  table.push_back("86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58");//down and left from 89 
  table.push_back("19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40");
  table.push_back("04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66");
  table.push_back("88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69");// to 73
  table.push_back("04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36");
  table.push_back("20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16");
  table.push_back("20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54");
  table.push_back("01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48");
                            //       //
  vector<int> numbers;
  tableStringToTableInt(table,numbers); //convert the number table of strings into
                                        //an array of integers essentially
  
  //now we have a vector of integers in order from left to right

  long long max=0;
  long long temp=0;
  int a,b,c,d;
  for(int i=0;i<400;i++){ //right
    if((((i+3)%20)>(i%20))&&((i+3)<=399)){
      temp=numbers[i]*numbers[i+1]*numbers[i+2]*numbers[i+3];
      if(temp>max){
        max=temp;
        a=i;
        b=i+1;
        c=i+2;
        d=i+3;
      }
    }
    if((i+60)<400){ //down
      temp=numbers[i]*numbers[i+20]*numbers[i+40]*numbers[i+60];
      if(temp>max){
        max=temp;
        a=i;
        b=i+20;
        c=i+40;
        d=i+60;
      }
    }
    if((((i+3)%20)>(i%20))&&((i+63)<400)){ //right down
      temp=numbers[i]*numbers[i+21]*numbers[i+42]*numbers[i+63];
      if(temp>max){
        max=temp;
        a=i;
        b=i+21;
        c=i+42;
        d=i+63;
      }
    }
    if((((i-3)%20)<(i%20))&&((i+57)<400)){ //left down
      temp=numbers[i]*numbers[i+19]*numbers[i+38]*numbers[i+57];
      if(temp>max){
        max=temp;
        a=i;
        b=i+19;
        c=i+38;
        d=i+57;
      }
    }
  }
  cout << "max: " << max << endl;
  cout << a << " " << b << " " << c << " " << d << endl;
}
