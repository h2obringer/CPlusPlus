#include<iostream>
#include "fraction.h"
#include "money.h"
using namespace std;

int gcd(int a,int b);

int main(){

	/*Fraction f1 = new Fraction(15,30);
	Fraction f2 = new Fraction(45,60);
	Fraction f3 = f1+f2;

	cout << f3.getTop() << endl;*/

	Money temp = new Money(100);
	Money temp2 = new Money(200);
	Money temp3 = temp+temp2;
	cout << temp3 << endl;
	cout << gcd(15,20) << endl;

}

int gcd(int a,int b){
	if(a==b){
		return a;
	}else if(a>b){
		return gcd(a-b,b);
	}else if(a<b){
		return gcd(a,b-a);
	}
}
