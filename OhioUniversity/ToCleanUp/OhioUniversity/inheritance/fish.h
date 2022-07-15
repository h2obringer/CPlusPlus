//************************************************************************
//File: fish.h
//
//Author: Randy Obringer
//
//Date Last Modified: ~2010
//
//Description: This is a child of the House class.
//	It inherits the input and output functions as well as the string called
//	description. It varies slightly from all the other children and is 
//	tailored to fish homes.
//************************************************************************

#ifndef FISH_H
#define FISH_H

#include "parent.h"
#include <iostream>
using namespace std;

class Fish:public House{
  public:
    Fish();
    void input(istream& ins); //my form of input
    void input2();
    void input3();
    void tank(string s);
    void Rarea(double d1,double d2);
    void Carea(double d1,double d2);
    void output(ostream& outs);
  private:
    string coral,rocks,filter,fresh_water,sea_weed,sand,salt_water,
    dirt,rectangle,cylinder,temp,name;
    double height,width,radius,area;
};

//constructor
Fish::Fish(){
	coral="coral"; 
	rocks="rocks"; 
	filter="filter"; 
	fresh_water="fresh water"; 
	sea_weed="sea weed"; 
	sand="sand"; 
	salt_water="salt water"; 
	dirt="dirt"; 
	rectangle="in a rectangular tank "; 
	cylinder="in a cylindrical tank ";
	name="Fish ||";
	tankType="";
	height=width=radius=area=0.0;
}

//output function to use with cout or a file stream
void Fish::output(ostream& outs){
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
void Fish::tank(string s){
	tankType=s;
}

//Compute area of a rectangular tank
void Fish::Rarea(double d1,double d2){
	area=d1*d2;
}

//Compute area of a circular tank
void Fish::Carea(double d1,double d2){
	area=3.14*d1*d1*d2;
}

//receive input from user or from file
void Fish::input(istream& ins){
	int choice3;
	if(ins==cin){
		cout << "Choose 1 for a rectangular tank" << endl;
		cout << "Choose 2 for a cylindrical tank" << endl;
		
		ins >> choice3;
		
		switch(choice3){
			case 1:
				cout << "Please enter the height of the tank" << endl;
				ins >> height;
				cout << "Please enter the width of the tank" << endl;
				ins >> width;
				tank(rectangle);
				Rarea(height,width);
				input2();
				break;
			case 2:
				cout << "Please enter the radius of the tank" << endl;
				ins >> radius;
				cout << "Please enter the height of the tank" << endl;
				ins >> height;
				tank(cylinder);
				Carea(radius,height);
				input2();
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
void Fish::input2(){
	int choice4;
	cout << "Choose 1 for fresh water" << endl;
	cout << "Choose 2 for salt water" << endl;
	cin >> choice4;
  
	switch(choice4){
		case 1: 
			if(description=="description:"){
				description = description + " " + fresh_water;
			}else{
				description = description + "," + fresh_water;
			}
			input3();
			break;
		case 2:
			if(description=="description:"){
				description = description + " " + salt_water;
			}else{
				description = description + "," + salt_water;
			}
			input3();
			break;
		default:
			cout << "That is not an option" << endl;
			break;
	}
}

//third round of user input
void Fish::input3(){ //my form of input
	int choice2;
	do{
		cout << "Choose 1 to add a coral" << endl;
		cout << "Choose 2 to add rocks" << endl;
		cout << "Choose 3 to add filter" << endl;
		cout << "Choose 4 to add sea_weed" << endl;
		cout << "Choose 5 to add sand" << endl;
		cout << "Choose 6 to add dirt" << endl;
		cout << "Choose 0 to make another order" << endl;
		cin >> choice2;
		
		switch(choice2){
			case 1: //add coral
				if(description=="description:"){
					description = description + " " + coral;
				}else{
					description = description + "," + coral;
				}
				cout << "Your " << description << endl;
				break;
			case 2: //add rocks
				if(description=="description:"){
					description = description + " " + rocks;
				}else{
					description = description + "," + rocks;
				}
				cout << "Your " << description << endl;
				break;
			case 3: //add filter
				if(description=="description:"){
					description = description + " " + filter;
				}else{
					description = description + "," + filter;
				}
				cout << "Your " << description << endl;
				break;
			case 4: //add sea weed
				if(description=="description:"){
					description = description + " " + sea_weed;
				}else{
					description = description + "," + sea_weed;
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
			case 6: //add dirt
				if(description=="description:"){
					description = description + " " + dirt;
				}else{
				  description = description + "," + dirt;
				}
				cout << "Your " << description << endl;
				break;
			case 0: //complete this fish
				return;
				break;
			default:
				cout << "That is not an option" << endl;
				break;
		}
	}while(choice2!=0);
}

#endif
