//************************************************************************
//File: insect.h
//
//Author: Randy Obringer
//
//Date Last Modified: ~2010
//
//Description: This is a child of the House class.
//	It inherits the input and output functions as well as the string called
//	description. It varies slightly from all the other children and is 
//	tailored to insect homes.
//************************************************************************

#ifndef INSECT_H
#define INSECT_H

#include <iostream>
#include "parent.h"
using namespace std;

class Insect:public House{
	public:
		Insect();
		void input(istream& ins); //my form of input
		void input2();
		void Rarea(double d1,double d2);
		void Sarea(double d1);
		void output(ostream& outs);
	private:
		string rotting_log,fresh_log,grass,sand,flowers,dirt,dead_leaves,name,holder,rectangle,sphere;
		double area,height,width,radius;
};

//constructor
Insect::Insect(){
	rotting_log="rotting log"; 
	fresh_log="fresh log"; 
	grass="grass"; 
	sand="sand"; 
	flowers="flowers"; 
	dirt="dirt"; 
	dead_leaves="dead leaves"; 
	name="Insect ||"; 
	holder="";
	rectangle=" in a rectangular glass holder ";
	sphere=" in a spherical glass holder ";
	area=height=width=radius=0.0;
}

//output function to use with cout or a file stream
void Insect::output(ostream& outs){
	if(outs==cout){
		outs << name << " " << description << holder << "with an area of " << area << endl;
	}else{
		outs << name << endl;
		outs << description << endl;
		outs << holder << endl;
		outs << area << endl;
	}
}

//Compute area of a rectangular holder
void Insect::Rarea(double d1,double d2){
	area=d1*d2;
}

//Compute area of a spherical holder
void Insect::Sarea(double d1){
	area=(4.0/3.0)*3.14*d1*d1*d1;
}

//receive input from user or from file
void Insect::input(istream& ins){
	int choice;
	if(ins==cin){
		cout << "Choose 1 for a rectangular glass holder" << endl;
		cout << "Choose 2 for a spherical glass holder" << endl;
		ins >> choice;
		
		switch(choice){
			case 1: //rectangular holder
				holder=rectangle;
				cout << "Please enter the height of the holder" << endl;
				ins >> height;
				cout << "Please enter the width of the holder" << endl;
				ins >> width;
				Rarea(height,width);
				input2();
				break;
			case 2: //spherical holder
				holder=sphere;
				cout << "Please enter the radius of the holder" << endl;
				ins >> radius;
				Sarea(radius);
				input2();
				break;
			default:
				cout << "That is not an option" << endl;
				break;
		}
	}else{ //read from file
		getline(ins,description);
		getline(ins,holder);
		ins >> area;
	}
}

void Insect::input2(){ //my form of input
	int choice2;
	do{
		cout << "Choose 1 to add a rotting log" << endl;
		cout << "Choose 2 to add a fresh log" << endl;
		cout << "Choose 3 to add grass" << endl;
		cout << "Choose 4 to add sand" << endl;
		cout << "Choose 5 to add dirt" << endl;
		cout << "Choose 6 to add dead leaves" << endl;
		cout << "Choose 7 to add flowers" << endl;
		cout << "Choose 0 to make another order" << endl;
		cin >> choice2;
		
		switch(choice2){
			case 1: //add rotting log
				if(description=="description:"){
					description = description + " " + rotting_log;
				}else{
					description = description + "," + rotting_log;
				}
				cout << "Your " << description << endl;
				break;
			case 2: //add fresh log
				if(description=="description:"){
					description = description + " " + fresh_log;
				}else{
					description = description + "," + fresh_log;
				}
				cout << "Your " << description << endl;
				break;
			case 3: //add grass
				if(description=="description:"){
					description = description + " " + grass;
				}else{
					description = description + "," + grass;
				}
				cout << "Your " << description << endl;
				break;
			case 4: //add sand
				if(description=="description:"){
					description = description + " " + sand;
				}else{
					description = description + "," + sand;
				}
				cout << "Your " << description << endl;
				break;
			case 5: //add dirt
				if(description=="description:"){
				  description = description + " " + dirt;
				}else{
					description = description + "," + dirt;
				}
				cout << "Your " << description << endl;
				break;
			case 6: //add dead leaves
				if(description=="description:"){
					description = description + " " + dead_leaves;
				}else{
					description = description + "," + dead_leaves;
				}
				cout << "Your " << description << endl;
				break;
			case 7: //add flower
				if(description=="description:"){
					description = description + " " + flowers;
				}else{
					description = description + "," + flowers;
				}
				cout << "Your " << description << endl;
				break;
			case 0: //complete this insect
				return;
				break;
			default:
				cout << "That is not an option" << endl;
				break;
		}
	}while(choice2!=0);
}


#endif
