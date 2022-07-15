#ifndef MONEY
#define MONEY
#include<iostream>
using namespace std;

class Money{
	public:
		friend Money operator +(const Money& amount1, const Money& amount2);
		friend Money operator -(const Money& amount1, const Money& amount2);
		friend Money operator -(const Money& amount);
		friend bool operator ==(const Money& amount1, const Money& amount2);
		Money(long dollars, int cents);
		Money(long dollars);
		Money();
		double get_value() const;
		void input(istream& ins);
		void output(ostream& outs) const;
		friend istream& operator >>(istream& ins, Money& amount);
		friend ostream& operator <<(ostream& outs, Money& amount);
	private:
		long all_cents;
};

#endif
