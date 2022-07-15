#ifndef FRACTION
#define FRACTION

class Fraction{
	public:
		//friend Fraction operator +(const Fraction& f1,const Fraction& f2);
		//friend Fraction operator -(const Fraction& f1,const Fraction& f2);
		Fraction(int top,int bottom);
		int getTop();
		int getBottom();
		
	private:
		int top;
		char divider;
		int bottom;
		int gcd(int a,int b);
};

#endif
