//************************************************************************
//Author: Randy Obringer
//File: Mammal.h
//Description:This is a child of the House class.
//It inherits the input and output functions as well as the string called
//description. It veries slightly from all the other children.
//************************************************************************
#ifndef MAMMAL_H
#define MAMMAL_H

#include <iostream>
#include "parent.h"
using namespace std;

class Mammal:public House{
  public:
    Mammal();
    void input(istream& ins); //my form of input
    void output(ostream& outs);
  private:
    string cave,rocks,grass,pond,trees,sand,plants,dirt,stream,name;//attributes and name
};

Mammal::Mammal(){
  cave="cave"; rocks="rocks"; grass="grass"; pond="pond"; trees="trees"; sand="sand";
  plants="plants"; dirt="dirt"; stream="stream"; name="Mammal ||";//since mammals are so diverse they can live anywhere. 
//This child gives mammals choices for a bigger area of land that can fit all the strings above in the same environment 
//if chosen.
}

void Mammal::output(ostream& outs){
  if(outs==cout)
    outs << name << " " << description << endl;
  else{
    outs << name << endl;
    outs << description << endl << endl;
  }
}

void Mammal::input(istream& ins){ //my form of input
  int choice2;
  if(ins==cin){
    do{
      cout << "Choose 1 to add a cave" << endl;
      cout << "Choose 2 to add rocks" << endl;
      cout << "Choose 3 to add grass" << endl;
      cout << "Choose 4 to add a pond" << endl;
      cout << "Choose 5 to add trees" << endl;
      cout << "Choose 6 to add sand" << endl;
      cout << "Choose 7 to add plants" << endl;
      cout << "Choose 8 to add dirt" << endl;
      cout << "Choose 9 to add a stream" << endl;
      cout << "Choose 0 to make another order" << endl;
      ins >> choice2;
      
      switch(choice2){
        case 1:
          if(description=="description:"){
            description = description + " " + cave;
          }else{
            description = description + "," + cave;
          }
          cout << "Your " << description << endl;
          break;
        case 2:
          if(description=="description:"){
            description = description + " " + rocks;
          }else{
            description = description + "," + rocks;
          }
          cout << "Your " << description << endl;
          break;
        case 3:
          if(description=="description:"){
            description = description + " " + grass;
          }else{
            description = description + "," + grass;
          }
          cout << "Your " << description << endl;
          break;
        case 4: 
          if(description=="description:"){
            description = description + " " + pond;
          }else{
            description = description + "," + pond;
          }
          cout << "Your " << description << endl;
          break;
        case 5:
          if(description=="description:"){
            description = description + " " + trees;
          }else{
            description = description + "," + trees;
          }
          cout << "Your " << description << endl;
          break;
        case 6:
          if(description=="description:"){
            description = description + " " + sand;
          }else{
            description = description + "," + sand;
          }
          cout << "Your " << description << endl;
          break;
        case 7:
          if(description=="description:"){
            description = description + " " + plants;
          }else{
            description = description + "," + plants;
          }
          cout << "Your " << description << endl;
          break;
        case 8:
          if(description=="description:"){
            description = description + " " + dirt;
          }else{
            description = description + "," + dirt;
          }
          cout << "Your " << description << endl;
          break;
        case 9:
          if(description=="description:"){
            description = description + " " + stream;
          }else{
            description = description + "," + stream;
          }
          cout << "Your " << description << endl;
          break;
        case 0:
          return;
          break;
        default:
          cout << "That is not an option" << endl;
      }
    }while(choice2!=0);
  }else{
    getline(ins,description);
  }
}

#endif
