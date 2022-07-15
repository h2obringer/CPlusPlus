#include <iostream>
using namespace std;

class Base{
	public:
		void Method1(){cout << "Base::Method1" << endl;}
		virtual void Method2(){cout << "Base::Method2" << endl;}
};

class Derived : public Base{
	public:
		void Method1(){cout << "Derived::Method1" << endl;}
		void Method2(){cout << "Derived::Method2" << endl;}
};

int main(){
	Base* obj = new Derived();
	//Note - constructed as Derived, but pointer stored as Base*
	
	obj->Method1(); //Prints "Base::Method1"
	obj->Method2(); //Prints "Derived::Method2"
}	
