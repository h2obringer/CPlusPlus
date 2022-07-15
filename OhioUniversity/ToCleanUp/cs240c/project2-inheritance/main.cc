//**************************************************************************
//Author: Randy Obringer
//File: main.cc
//Description: This is the application of the program. It allows for the 
//input of each child to be made correctly from reading from file as well
//as user made input. It uses the universal list to hold the input together.
//It used an external iterator to output the data both to the screen and to
//the data.txt file so that data may be accessed during later sessions of the
//program. 
//**************************************************************************
//EXTRA CREDIT for turning this project in so extremely early and by having
//everything working properly even though I can only make it to 75% of all 
//classes???????????????????????????????????????????????????????????????????
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
  House *tmp;

  ifstream in;
  string temp1;
  in.open("data.txt");
  getline(in,temp1);
  while(!in.fail()){
    if(!in.eof()){
      if(temp1=="Amphibian ||"){
        tmp=new Amphibian;
        tmp->input(in);
        myhomes.push_back(tmp);
        getline(in,temp1);
      }else if(temp1=="Insect ||"){
        tmp=new Insect;
        tmp->input(in);
        myhomes.push_back(tmp);
        getline(in,temp1);
      }else if(temp1=="Fish ||"){
        tmp=new Fish;
        tmp->input(in);
        myhomes.push_back(tmp);
        getline(in,temp1);
      }else if(temp1=="Reptile ||"){
        tmp=new Reptile;
        tmp->input(in);
        myhomes.push_back(tmp);
        getline(in,temp1);
      }else if(temp1=="Mammal ||"){
        tmp=new Mammal;
        tmp->input(in);
        myhomes.push_back(tmp);
        getline(in,temp1);
      }else if(temp1=="Bird ||"){
        tmp=new Bird;
        tmp->input(in);
        myhomes.push_back(tmp);
        getline(in,temp1);
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

