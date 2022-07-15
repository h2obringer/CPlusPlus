//***************************************************************************
//Author: Randy Obringer
//
//Program: odometer.cc
//
//Date: ~2009
//
//Description: This program will give a menu for the user to use to either
//view or input information about their driving. You can save the data for
//later use as well as load up previous data. 
//
//***************************************************************************

#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

class MPG_Odometer{
	public:
		void MPG_average();
		double recent_MPG();
		void initiate_values();
		void reset_totals();
		void show_totals();
		void fillUpInfo(); 
		void resume();
		void save_dat();
		void load_dat();

	private:
		double ave_MPG,MPG, gallons, miles, total_gals, total_miles;
		string answer;
		ifstream in_stream;
		ofstream out_stream;
};

int main(){
  
	MPG_Odometer Odometer;
	int choice;
  
	Odometer.initiate_values();  

	do{
		cout << "Choose 1 to enter the most recent fill-up information.\n";
		cout << "Choose 2 to reset the totals.\n";
		cout << "Choose 3 to view overall and most recent MPG's.\n";
		cout << "Choose 4 to view the mileage and/or gallon totals.\n";
		cout << "Choose 5 to save data for the next session.\n";
		cout << "(Cycle through all previous choices before hand)\n";
		cout << "Choose 6 to load data from the last session. \n";
		cout << "Choose 7 to Quit.\n";
		cin >> choice;
		  
		switch(choice){
			case 1: //enter most recent fill up info
				Odometer.fillUpInfo();
				Odometer.resume();
				break;
			case 2: //reset the totals
				Odometer.reset_totals();
				Odometer.resume();
				break;
			case 3: //view overall and most recent MPG readings
				Odometer.MPG_average();
				Odometer.resume();
				break;
			case 4: //view mileage and or gallon totals
				Odometer.show_totals();
				Odometer.resume();
				break;
			case 5: //save data 
				Odometer.save_dat();
				Odometer.resume();
				break;
			case 6: //load data
				Odometer.load_dat();
				Odometer.resume();
				break;
			case 7: //end program
				cout<< "End of Program.\n";
				break;
			default:
				cout << "Not a valid choice.\n"
				<< "Choose again.\n";
		}
    }while(choice != 7);
	
	return 0;
}

void MPG_Odometer::initiate_values(){
	MPG=gallons=miles=total_gals=total_miles=0;
}

void MPG_Odometer::reset_totals(){
	total_gals=total_miles=0;
	cout << "Totals have been reset!" << endl;
}

void MPG_Odometer::show_totals(){
	cout << "The total amount of miles you have driven is:\n";
	cout << total_miles << endl;
	cout << "The total amount of gallons pumped into your tank is:\n";
	cout << total_gals << endl;
}

double MPG_Odometer::recent_MPG(){
	MPG=gallons/miles;
	return MPG;
}

void MPG_Odometer::MPG_average(){
	total_miles+=miles;
	total_gals+=gallons;
	ave_MPG=total_miles/total_gals;
	cout << "Your average MPG is:\n";
	cout << ave_MPG << endl;
	cout << "Your recent MPG is:\n";
	cout << MPG << endl;
}

void MPG_Odometer::fillUpInfo(){
	cout << "Please enter the amount of miles driven since the last fill-up:\n";
	cin >> miles;
	cout << endl;
	cout << "Please enter the gallons pumped into the tank:\n";
	cin >> gallons;
	cout << endl; 
	MPG=miles/gallons;
}

void MPG_Odometer::resume(){
	char c;
	do{
		cout << "Press enter  to continue:" << endl;
		if(cin.peek()=='\n'){
			cin.ignore();
		}
		cin.get(c);
		if(c!='\n'){
			cout << "You did not press enter, please try again:" << endl;
		}
	}while(c!='\n');
}

void MPG_Odometer::save_dat(){
	out_stream.open("data.log");
	if(out_stream.fail()){
		cout << "Output file openning failed.\n";
		exit(1);
	}
	out_stream << total_miles << endl;
	out_stream << total_gals << endl;
	out_stream.close();
}

void MPG_Odometer::load_dat(){
	in_stream.open("data.log");
	if(in_stream.fail()){
		cout << "Input file openning failed.\n";
		exit(1);
	}
	in_stream >> total_miles;
	in_stream >> total_gals;
	in_stream.close();
}
