/*
* Author: Randal Obringer
* Date: 10 March 2014
* Description: A metric ton is 35,273.92 ounces. Write a program that will read the weight of 
* a package of breakfast cereal in ounces and output the weight in metric tons as well as the 
* number of boxes needed to yield one metric ton of cereal. Your program should allow the user 
* to repeat this calculation as often as the user wishes.
*/

#include <iostream>
#include <string>
using namespace std;

int main(){
	const double METRIC_TON = 35273.92; //ounces in a metric ton
	double cerealInOunces;
	double cerealInMetricTons;
	double numberOfBoxesNeeded;
	bool proceed = true;
	bool goodInput = false;
	string input = "";//NULL; 

	do{
		cout << "Please enter the weight of a cereal box in ounces:" << endl;
		cin >> cerealInOunces;
		cerealInMetricTons = cerealInOunces / METRIC_TON;
		numberOfBoxesNeeded = METRIC_TON / cerealInOunces;
		cout << "Your box of cereal weighs " << cerealInMetricTons << " metric tons." << endl;
		cout << "It would take " << numberOfBoxesNeeded << " boxes of that cereal to make a metric ton." << endl;
		do{
			cout << "Would you like to continue?" << endl;
			cin >> input;
			if (input[0] == 'y' || input[0] == 'Y'){
				goodInput = true;
				proceed = true;
			}else if (input[0] == 'n' || input[0] == 'N'){
				goodInput = true;
				proceed = false;
			}else{
				cout << "Please enter yes or no" << endl;
				goodInput = false;
			}
		} while (!goodInput);
	} while (proceed);
}