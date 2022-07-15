//**************************************************************************
//File: main.cc
//
//Author: Randy Obringer
//
//Date Last Modified: ~2010
//
//Description: Input data for each animal type. It uses the universal list  
//	from class inheritance to hold the input together.
//	It uses an external iterator to output the data both to the screen and to
//	the data.txt file so that data may be accessed during later sessions of the
//	program. 
//**************************************************************************

#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <fstream>
#include "parent.h"
#include "reptile.h"
#include "bird.h"
#include "fish.h"
#include "mammal.h"
#include "insect.h"
#include "amphibian.h"
using namespace std;

int main(){
	list<House*> myhomes;
	list<House*>::iterator it;
	int choice;
	House *tmp; //create temporary animal house pointer to hold all types of animals

	//start the file stream
	ifstream in;
	string animalType;
	in.open("data.txt");
	getline(in,animalType);
	
	//read from file
	while(!in.fail()){
		if(!in.eof()){
			if(animalType=="Amphibian ||"){
				tmp=new Amphibian;
				tmp->input(in);
				myhomes.push_back(tmp);
				getline(in,animalType);
			}else if(animalType=="Insect ||"){
				tmp=new Insect;
				tmp->input(in);
				myhomes.push_back(tmp);
				getline(in,animalType);
			}else if(animalType=="Fish ||"){
				tmp=new Fish;
				tmp->input(in);
				myhomes.push_back(tmp);
				getline(in,animalType);
			}else if(animalType=="Reptile ||"){
				tmp=new Reptile;
				tmp->input(in);
				myhomes.push_back(tmp);
				getline(in,animalType);
			}else if(animalType=="Mammal ||"){
				tmp=new Mammal;
				tmp->input(in);
				myhomes.push_back(tmp);
				getline(in,animalType);
			}else if(animalType=="Bird ||"){
				tmp=new Bird;
				tmp->input(in);
				myhomes.push_back(tmp);
				getline(in,animalType);
			}
		}
	}in.close();
	  

	  //switch statement menu
	  do{
		cout << "Choose 1 to order a home for a bird" << endl;
		cout << "Choose 2 to order a home for a fish" << endl;
		cout << "Choose 3 to order a home for an amphibian" << endl;
		cout << "Choose 4 to order a home for a reptile" << endl;
		cout << "Choose 5 to order a home for an insect" << endl;
		cout << "Choose 6 to order a home for a mammal" << endl;
		cout << "Choose 7 to view your selections" << endl;
		cout << "Choose 8 to exit the program" << endl;
		cin >> choice;

		switch(choice){
		  case 1:
			tmp=new Bird;
			tmp->input(cin);
			myhomes.push_back(tmp);
			break;
		  case 2:
			tmp=new Fish;
			tmp->input(cin);
			myhomes.push_back(tmp);
			break;
		  case 3:
			tmp=new Amphibian;
			tmp->input(cin);
			myhomes.push_back(tmp);
			break;
		  case 4:
			tmp=new Reptile;
			tmp->input(cin);
			myhomes.push_back(tmp);
			break;
		  case 5:
			tmp=new Insect;
			tmp->input(cin);
			myhomes.push_back(tmp);
			break;
		  case 6:
			tmp=new Mammal;
			tmp->input(cin);
			myhomes.push_back(tmp);
			break;
		  case 7:
			for(it=myhomes.begin();it!=myhomes.end();++it){
			  (*it)->output(cout);
			  cout << endl;
			}
			break;
		  case 8:
			cout << "End of program" << endl;
			break;
		  default:
			cout << "That is not a choice" << endl;
		}
	  }while(choice!=8);        

	ofstream out;
	out.open("data.txt");
	for(it=myhomes.begin();it!=myhomes.end();++it){
	  (*it)->output(out);
	}

}

