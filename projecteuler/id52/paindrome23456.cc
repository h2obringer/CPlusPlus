#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <sstream>
using namespace std;

string convertLLString(unsigned long long n){
  ostringstream out;
  out << n;
  return out.str();
};

int main(){
  string current,_2,_3,_4,_5,_6,creversed,temp="";
  unsigned long long i_2;
  unsigned long long i_3;
  unsigned long long i_4;
  unsigned long long i_5;
  unsigned long long i_6;
  unsigned long long a=125874; //18,446,744,073,709,551,615 is largest possible with this data type
  unsigned long long max6=3074457345618258602;
  int l;
  unsigned long long count=0;
  for(unsigned long long i=a;i<max6;i++){
    current=convertLLString(i);
    l=current.length();
    creversed="";
    for(int j=0;j<l;j++){
      temp=creversed;
      creversed=current[j]+temp;
    }
    i_2=i*2;
    _2=convertLLString(i_2);
    if(_2==creversed){
      i_3=i*3;
      _3=convertLLString(i_3);
      if(_3==creversed){
        i_4=i*4;
        _4=convertLLString(i_4);
        if(_4==creversed){
          i_5=i*5;
          _5=convertLLString(i_5);
          if(_5==creversed){
            i_6=i*6;
            _6=convertLLString(i_6);
            if(_6==creversed){
              cout << "Answer: " << i << endl;
              exit(-1);
            }
          }
        }
      }
    }
  }
}
