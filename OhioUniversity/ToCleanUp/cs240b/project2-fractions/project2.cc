//I had trouble compiling my project as seperate files so I thought I would give
//you a file that actually works and that is not seperated. 

#include <iostream>
using namespace std;

//class definition
class fraction{
public:
  fraction();
  void input();
  fraction output();
  //void simplist_terms(int a,int b);
  // 
  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  // ||||||||||||||||||||||||||||||||  
  //attempt at getting fractions to lowest
  //terms it does not work and I have tried a million different ways :(
  fraction operator+(fraction const& fract);
  fraction operator-(fraction const& fract);
  fraction operator*(fraction const& fract);
  fraction operator/(fraction const& fract);

  friend ostream &operator<<(ostream &outs, const fraction &frac);
  friend istream &operator>>(istream &ins, fraction &frac);
  
  int a,b;
  char divider;
  
};
//*****************************************************************************
//Author: Randy Obringer
// 
//File: Project2
//Description: This program was to practice creating abstract data types.
//It allows the user to input 2 different fractions and it will spit out the
//correct values for all of the standard operations of those 2 fractions 
//(addition, subtraction, multiplication, and division)
//
//Date: Thursday January 21, 2010. 
//*****************************************************************************

int main(){
  fraction frac1,frac2,frac3;
  
  cout << "Please enter 2 fractions:" << endl;
  frac1.input();
  frac2.input();
  
  frac3=frac1+frac2;
  //frac3.simplist_terms(frac3.a,frac3.b);

  cout << "The addition of " << frac1 << " and " << frac2 << " is:" << frac3 << endl;
  frac3=frac1-frac2;
  //frac3.simplist_terms(frac3.a,frac3.b);

  cout << "The subtraction of " << frac2 << " from " << frac1 << " is:" << frac3 << endl;
  frac3=frac1*frac2;
  //frac3.simplist_terms(frac3.a,frac3.b);

  cout << "The product of " << frac1 << " and " << frac2 << " is:" << frac3 << endl;
  frac3=frac1/frac2;
  //frac3.simplist_terms(frac3.a,frac3.b);

  cout << "The division of " << frac1 << " by " << frac2 << " is:" << frac3 << endl;

}

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
