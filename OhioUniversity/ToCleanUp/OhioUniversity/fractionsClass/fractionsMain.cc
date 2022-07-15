//*****************************************************************************
//Author: Randy Obringer
// 
//File: FractionsMain.cc
//Description: This program was to practice creating abstract data types.
//It allows the user to input 2 different fractions and it will spit out the
//correct values for all of the standard operations of those 2 fractions 
//(addition, subtraction, multiplication, and division)
//
//Date: Thursday January 21, 2010. 
//*****************************************************************************

#include "class.h"
#include <iostream>
using namespace std;

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
