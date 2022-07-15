#include "class.h"
#include <iostream>
using namespace std;


//class implementation
fraction::fraction(){
  a=b=0;
}

fraction fraction::output(){
  cout << a << divider << b;
}

void fraction::input(){
  cin >> a;
  cin >> divider;
  cin >> b;
}

/*void fraction::simplist_terms(int c, int d){
  fraction frac;
  int i;
  frac.a=c;    //This function does not work for some reason and I have no idea
  frac.b=d;    //why... I worked on it trying different parameters and making it
  if(c>d){     //a friend and everything but nothing worked for me! UGH
    i=c;
  }else{
    i=d;
      }
  while((c%i!=0)&&(d%i!=0)&&(i>0)){
    i--;
  }
    frac.a=(frac.a/i);
    frac.b=(frac.b/i);
    c=frac.a;
    d=frac.b;
 }*/

//Allows for the addition of 2 fraction types
fraction fraction::operator+(fraction const& fract){
  fraction frac3;
  frac3.a=(a*fract.b)+(b*fract.a);
  frac3.divider=fract.divider;
  frac3.b=(b*fract.b);
  return frac3;
}
//Allows for the subtration of 2 fraction types
fraction fraction::operator-(fraction const& fract){
  fraction frac3;
  frac3.a=(a*fract.b)-(b*fract.a);
  frac3.divider=fract.divider;
  frac3.b=(b*fract.b);
  return frac3;
}
//Allows for the multiplication of 2 fraction types
fraction fraction::operator*(fraction const& fract){
  fraction frac3;
  frac3.a=a*fract.a;
  frac3.divider=fract.divider;
  frac3.b=b*fract.b;
  return frac3;
}
//Allows for the division of 2 fraction types
fraction fraction::operator/(fraction const& fract){
  fraction frac3;
  frac3.a=a*fract.b;
  frac3.divider=fract.divider;
  frac3.b=b*fract.a;
  return frac3;
}
//Allows for the simple output of multiple fraction types
ostream &operator<<(ostream &outs, const fraction &frac){
   outs << frac.a << frac.divider << frac.b;
  return outs;
}

//Allows for the simple input of multiple fraction types
istream &operator>>(istream &ins, fraction &frac){
  ins >> frac.a >> frac.divider >> frac.b;
  return ins;
}
