#include "money.h"

Money::Money(){
	all_cents=0;
}

Money::Money(long dollars){
	Money temp;
	temp.all_cents=dollars*100;
}

Money operator +(const Money& amount1, const Money& amount2){
	Money temp;
	temp.all_cents = amount1.all_cents+amount2.all_cents;
	return temp;
}

ostream& operator <<(ostream& outs, const Money& amount){
	outs << "$" << amount.all_cents << endl;
	return outs;
}
		/*friend Money operator -(const Money& amount1, const Money& amount2);
		friend Money operator -(const Money& amount);
		friend bool operator ==(const Money& amount1, const Money& amount2);
		Money(long dollars, int cents);
		Money(long dollars);
		Money();
		double get_value() const;
		void input(istream& ins);
		void output(ostream& outs) const;*/
