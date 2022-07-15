/*
* Author: Randal Obringer
*
* Description: Vehicle Registration class.
*
* Date Last Modified: ~2009
*/

#ifndef vregistration_h
#define vregistration_h

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class vregistration{
	public:
		vregistration();			//Constructor function
		istream& input_data(istream& ins);	//input function
		ostream& output_data(ostream& outs);	//output function
		string get_owner()const{return owner;} //Accessor functions - Helpful for getting information
		string get_license_plate()const{return license_plate;} //for a single piece of information
		string get_make()const{return make;}	 //from a specific vehicle registration
		string get_model()const{return model;} //
		int get_year()const{return year;}	 //
  
	private:
		string owner;			//needed for data
		string license_plate;
		string make;
		string model;
		int year;
};

istream& operator>>(istream& in,vregistration& temp);   //Helpful for use from database.cc
ostream& operator<<(ostream& out,vregistration& temp);  //Helpful for use from database.cc

#endif
