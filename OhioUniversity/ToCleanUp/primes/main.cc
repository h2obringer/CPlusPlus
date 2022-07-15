#include <iostream>
using namespace std;

//as long as the number doesn't contain a prime number greater than 13
//the output will be correct. If anything larger is in the number there could be a problem
void printPrimes(int x){
	if(x==1){
		cout << "1" << endl;
	}else if(x%2==0){
		if(x/2==0){
			cout << "2" << endl;
		}else{
			cout << "2*";
			printPrimes(x/2);
		}
	}else if(x%3==0){
		if(x/3==0){
			cout << "3" << endl;
		}else{
			cout << "3*";
			printPrimes(x/3);
		}
	}else if(x%5==0){
		if(x/5==0){
			cout << "5" << endl;
		}else{
			cout << "5*";
			printPrimes(x/5);
		}
	}else if(x%7==0){
		if(x/7==0){
			cout << "7" << endl;
		}else{
			cout << "7*";
			printPrimes(x/7);
		}
	}else if(x%11==0){
		if(x/11==0){
			cout << "11" << endl;
		}else{
			cout << "11*";
			printPrimes(x/11);
		}
	}else{
		cout << x << endl;
	}
}

int main(){
	//printPrimes(143);
	printPrimes(200000);
	//printPrimes(169); //this doesn't work at all.
}
