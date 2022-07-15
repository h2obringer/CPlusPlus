#include <iostream>
using namespace std;

template<class T> //can have 2 template variables: template<class T1,class T2>
//all template variables must be used.
void swap_values(T& variable1, T& variable2){
	T temp;
	temp=variable1;
	variable1=variable2;
	variable2=temp;
}

int main(){
	int i1=1,i2=2;
	cout << "Original values are: " << i1 << " and " << i2 << endl;
	swap_values(i1,i2);
	cout << "After: " << i1 << " and " << i2 << endl;

	char c1='c',c2='d';
	cout << "Original values are: " << c1 << " and " << c2 << endl;
	swap_values(c1,c2);
	cout << "After: " << c1 << " and " << c2 << endl;
	
}
