//************************************************************************
//File: bird.h
//
//Author: Randy Obringer
//
//Date Last Modified: ~2010
//
//Description: This is a child of the House class.
//	It inherits the input and output functions as well as the string called
//	description. It varies slightly from all the other children and is 
//	tailored to bird homes.
//************************************************************************

#ifndef BIRD_H
#define BIRD_H

#include <iostream>
#include "parent.h"
using namespace std;

class Bird:public House{
	public:
		Bird();
		void input(istream& ins); //my form of input
		void input2();
		void input3();
		void output(ostream& outs);
	private:
		string branches,twigs,dirt,grass,hay,name,birdhouse,nest;
		double diameter,depth,height;
		int yes;
};

//constructor
Bird::Bird(){
	branches="branches"; 
	twigs="twigs"; 
	hay="hay"; 
	dirt="dirt"; 
	grass="grass"; 
	nest="nest"; 
	birdhouse="bird house"; 
	name="Bird ||";
	diameter=depth=height=0.0;
	yes=0;
}

//receive input from user or from file
void Bird::input(istream& ins){
	int choice;
	if(ins==cin){
		cout << "Choose 1 for a bird house" << endl;
		cout << "Choose 2 for a nest" << endl;
		ins >> choice;
		
		switch(choice){
			case 1:
				if(description=="description:"){
					description = description + " " + birdhouse;
				}else{
					description = description + "," + birdhouse;
				}
				cout << "Please enter the height at which the bird house will be placed:" << endl;
				ins >> height;
				yes=0;
				input3();
				break;
			case 2:
				if(description=="description:"){
					description = description + " " + nest;
				}else{
					description = description + "," + nest;
				}
				cout << "Please enter the diameter of the nest:" << endl;
				ins >> diameter;
				cout << "Please enter the depth of the nest:" << endl;
				ins >> depth;
				cout << "Please enter the height at which the nest will be placed:" << endl;
				ins >> height;
				yes=1;
				input2();
				break;
			default:
				cout << "That is not an option" << endl;
				break;
		}
	}else{ //read from file
		ins >> yes;
		if(ins.peek()=='\n')ins.ignore();
		if(yes==0){
			getline(ins,description);
			ins >> height;
		}else{
			getline(ins,description);
			ins >> diameter;
			ins >> depth;
			ins >> height;
		}
	}
}

//second round of input
void Bird::input2(){
	int choice2;
	do{
		cout << "Choose 1 to add branches" << endl;
		cout << "Choose 2 to add twigs" << endl;
		cout << "Choose 3 to add hay" << endl;
		cout << "Choose 4 to add dirt" << endl;
		cout << "Choose 5 to add grass" << endl;
		cout << "Choose 0 to make another order" << endl;
		cin >> choice2;
		
		switch(choice2){
			case 1:
				if(description=="description:"){
					description = description + " " + branches;
				}else{
					description = description + "," + branches;
				}
				cout << "Your " << description << endl;
				break;
			case 2:
				if(description=="description:"){
					description = description + " " + twigs;
				}else{
					description = description + "," + twigs;
				}
				cout << "Your " << description << endl;
				break;
			case 3:
				if(description=="description:"){
					description = description + " " + hay;
				}else{
					description = description + "," + hay;
				}
				break;
			case 4:
				if(description=="description:"){
					description = description + " " + dirt;
				}else{
					description = description + "," + dirt;
				}
				cout << "Your " << description << endl;
				break;
			case 5:
				if(description=="description:"){
					description = description + " " + grass;
				}else{
					description = description + "," + grass;
				}
				cout << "Your " << description << endl;
				break;
			case 0:
				return;
				break;
			default:
				cout << "That is not an option" << endl;
				break;
		}
	}while(choice2!=0);
}

//third round of input
void Bird::input3(){
	int choice2;
	do{
		cout << "Choose 1 to add hay" << endl;
		cout << "Choose 2 to add grass" << endl;
		cout << "Choose 0 to make another order" << endl;
		cin >> choice2;
		
		switch(choice2){
			case 1:
				if(description=="description:"){
					description = description + " " + hay;
				}else{
					description = description + "," + hay;
				}
				break;
			case 2:
				if(description=="description:"){
					description = description + " " + grass;
				}else{
					description = description + "," + grass;
				}
				cout << "Your " << description << endl;
				break;
			case 0:
				return;
				break;
			default:
				cout << "That is not an option" << endl;
				break;
		}
	}while(choice2!=0);
}

//output function to use with cout or a file stream
void Bird::output(ostream& outs){
	if(outs==cout){
		if(yes==0){
			outs << name << " " << description << ", at a height of " << height << endl;
		}else{
			outs << name << " " << description << ", with a diameter of " << diameter 
			<< " and a depth of " << depth << " at a height of " << height << endl;
		}
	}else{
		if(yes==0){
			outs << name << endl;
			outs << yes << endl;
			outs << description << endl;
			outs << height << endl;
		}else{
			outs << name << endl;
			outs << yes << endl;
			outs << description << endl;
			outs << diameter << endl;
			outs << depth << endl;
			outs << height << endl;
		}
	}
}

#endif
