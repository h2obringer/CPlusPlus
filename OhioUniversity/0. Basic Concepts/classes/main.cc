#include <iostream>
using namespace std;

class myClass{
	public:
		myClass(int number);
		int getNumber();
		void setNumber(int number);
	private:
		int number;
};

int main(){
	myClass c = new myClass(1);
	cout << "The number is: " << c.getNumber() << endl;
	c.setNumber(2);
	cout << "The number is now: " << c.getNumber() << endl;
}

myClass::myClass(int number){
	this.number=number;
}

int myClass::getNumber(){
	return number;
}

void myClass:: setNumber(int number){
	this.number=number;
}
