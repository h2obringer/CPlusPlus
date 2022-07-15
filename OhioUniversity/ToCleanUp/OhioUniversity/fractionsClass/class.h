/* Author: Randal Obringer
* Date Last Modified: Thursday January 21, 2010.
* Description: Fraction class header that overloads math operations to use on fractions
*/

#ifndef CLASS_H
#define CLASS_H

class fraction{
	public:
		fraction();
		void input();
		fraction output();
		//void simplist_terms(int a,int b); //TODO
		fraction operator+(fraction const& fract);
		fraction operator-(fraction const& fract);
		fraction operator*(fraction const& fract);
		fraction operator/(fraction const& fract);

		friend ostream &operator<<(ostream &outs, const fraction &frac);
		friend istream &operator>>(istream &ins, fraction &frac);
  
		int a,b;
		char divider;
};

#endif
