/*
* Author: Randal Obringer
*
* Description: Vehicle Registration class.
*
* Date Last Modified: ~2009
*/

#include "vregistration.h"
using namespace std;

//constructor
vregistration::vregistration(){  
	owner=license_plate=make=model=" ";
	year=0;
}

//overloaded input operator makes for ease of input
istream& operator>>(istream& in,vregistration& temp){
	temp.input_data(in);
	return in;
}

//Needed for overloaded operator and inputing data for vehicle registration
istream& vregistration::input_data(istream& ins){ 
	if(ins.peek()=='\n'){		
		ins.ignore();
	}
	if(ins==cin){cout << "Owner of Vehicle:\n";}
	getline(ins,owner);
	if(ins==cin){cout << "License Plate Number:\n";}
	getline(ins,license_plate);
	if(ins==cin){cout << "Make:\n";}
	getline(ins,make);
	if(ins==cin){cout << "Model:\n";}
	getline(ins,model);
	if(ins==cin){cout << "Year:\n";}
	ins >> year;
	return ins;
}

//overloaded output operator
ostream& operator<<(ostream& out,vregistration& temp){  
	temp.output_data(out);
	return out;
}

//Needed for overloaded operator and outputting data for vehicle registrations
ostream& vregistration::output_data(ostream& outs){  
	if(outs==cout){outs << "Owner of Vehicle:\n";}
	outs << owner << endl;
	if(outs==cout){outs << "License Plate Number:\n";}
	outs << license_plate << endl;
	if(outs==cout){outs << "Make:\n";}
	outs << make << endl;
	if(outs==cout){outs << "Model:\n";}
	outs << model << endl;
	if(outs==cout){outs << "Year:\n";}
	outs << year << endl;
	if(outs==cout){outs << endl;}
	return outs;
}


