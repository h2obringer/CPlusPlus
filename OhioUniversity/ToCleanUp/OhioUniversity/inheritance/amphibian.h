//************************************************************************
//File: amphibian.h
//
//Author: Randy Obringer
//
//Date Last Modified: ~2010
//
//Description: This is a child of the House class.
//	It inherits the input and output functions as well as the string called
//	description. It varies slightly from all the other children and is 
//	tailored to amphibian homes.
//************************************************************************

#ifndef AMPHIBIAN_H
#define AMPHIBIAN_H

#include "parent.h"
#include <iostream>
using namespace std;

class Amphibian:public House{
	public:
		Amphibian();
		void input(istream& ins); //my form of input
		void input2();
		void tank(string s);
		void Rarea(double d1,double d2);
		void Carea(double d1,double d2);
		void output(ostream& outs);
	private:
		string lillipad,rock,dirt,grass,sand,cylinder,rectangle,tankType,name;
		double radius,height,width,area;
};

//constructor
Amphibian::Amphibian(){
	lillipad="lillipad"; 
	rock="rock"; 
	sand="sand";
	dirt="dirt"; 
	grass="grass";
	name="Amphibian ||";
	cylinder="in a cylindrical tank "; 
	rectangle="in a rectangular tank "; 
	tankType="";
	radius=height=width=area=0.0;
}

//output function to use with cout or a file stream
void Amphibian::output(ostream& outs){
	if(outs==cout){
		outs << name << " " << description << " " << tankType << "with an area of " << area << endl;
	}else{
		outs << name << endl;
		outs << description << endl;
		outs << tankType << endl;
		outs << area << endl;
	}
}

//assign the tank type
void Amphibian::tank(string s){
	tankType=s;
}

//Compute area of a rectangular tank
void Amphibian::Rarea(double d1,double d2){
	area=d1*d2;
}

//Compute area of a circular tank
void Amphibian::Carea(double d1,double d2){
	area=3.14*d1*d1*d2;
}

//receive input from user or from file
void Amphibian::input(istream& ins){
	int choice3;
	if(ins==cin){
		cout << "Choose 1 for a rectangular tank" << endl;
		cout << "Choose 2 for a cylindrical tank" << endl;
		
		ins >> choice3;
		
		switch(choice3){
			case 1: //Recatangular Tank
				cout << "Please enter the height of the tank" << endl;
				ins >> height;
				cout << "Please enter the width of the tank" << endl;
				ins >> width;
				tank(rectangle);
				Rarea(height,width);
				input2(); //continue with user input
				break;
			case 2: //Circular Tank
				cout << "Please enter the radius of the tank" << endl;
				ins >> radius;
				cout << "Please enter the height of the tank" << endl;
				ins >> height;
				tank(cylinder);
				Carea(radius,height);
				input2(); //continue with user input
				break;
			default:
				cout << "That is not an option" << endl;
				break;
		}     
	}else{ //read from file
		getline(ins,description);
		getline(ins,tankType);
		ins >> area;
	}
}

//second round of user input
void Amphibian::input2(){ 
	int choice2;
	do{
		cout << "Choose 1 to add a lillipad" << endl;
		cout << "Choose 2 to add a rock" << endl;
		cout << "Choose 3 to add dirt" << endl;
		cout << "Choose 4 to add grass" << endl;
		cout << "Choose 5 to add sand" << endl;
		cout << "Choose 0 to make another order" << endl;
		cin >> choice2;
		
		switch(choice2){
			case 1: //add a lillipad
				if(description=="description:"){
					description = description + " " + lillipad;
				}else{
					description = description + "," + lillipad;
				}
				cout << "Your " << description << endl;
				break;
			case 2: //add a rock
				if(description=="description:"){
					description = description + " " + rock;
				}else{
					description = description + "," + rock;
				}
				cout << "Your " << description << endl;
				break;
			case 3: //add dirt
				if(description=="description:"){
					description = description + " " + dirt;
				}else{
					description = description + "," + dirt;
				}
				cout << "Your " << description << endl;
				break;
			case 4: //add grass
				if(description=="description:"){
					description = description + " " + grass;
				}else{
					description = description + "," + grass;
				}
				cout << "Your " << description << endl;
				break;
		  case 5: //add sand
				if(description=="description:"){
					description = description + " " + sand;
				}else{
					description = description + "," + sand;
				}
				cout << "Your " << description << endl;
				break;
		  case 0: //complete this amphibian 
				return;
				break;
		  default:
				cout << "That is not an option" << endl;
				break;
		}
	}while(choice2!=0);
}

#endif
