//************************************************************************
//Author: Randy Obringer
//File: Insect.h
//Description: This is a child of the House class.
//It inherits the input and output functions as well as the string called
//description. It veries slightly from all the other children.
//************************************************************************
//COMPLETE!!!
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
    string rotting_log,fresh_log,grass,sand,flowers,dirt,dead_leaves,name,temp,rectangle,sphere;
    double dtemp,height,width,radius;
};

Insect::Insect(){
  rotting_log="rotting log"; fresh_log="fresh log"; grass="grass"; sand="sand"; 
  flowers="flowers"; dirt="dirt"; 
  dead_leaves="dead leaves"; name="Insect ||"; temp="";rectangle=" in a rectangular glass holder ";
  sphere=" in a spherical glass holder ";
  dtemp=height=width=radius=0.0;
}

void Insect::output(ostream& outs){
  if(outs==cout)
    outs << name << " " << description << temp << "with an area of " << dtemp << endl;
  else{
    outs << name << endl;
    outs << description << endl;
    outs << temp << endl;
    outs << dtemp << endl;
  }
}

void Insect::Rarea(double d1,double d2){
  dtemp=d1*d2;
}

void Insect::Sarea(double d1){
  dtemp=(4.0/3.0)*3.14*d1*d1*d1;
}

void Insect::input(istream& ins){
  int choice;
  if(ins==cin){
    cout << "Choose 1 for a rectangular glass holder" << endl;
    cout << "Choose 2 for a spherical glass holder" << endl;
    ins >> choice;
    
    switch(choice){
      case 1: 
        temp=rectangle;
        cout << "Please enter the height of the holder" << endl;
        ins >> height;
        cout << "Please enter the width of the holder" << endl;
        ins >> width;
        Rarea(height,width);
        input2();
        break;
      case 2:
        temp=sphere;
        cout << "Please enter the radius of the holder" << endl;
        ins >> radius;
        Sarea(radius);
        input2();
        break;
      default:
        cout << "That is not an option" << endl;
    }
  }else{
    getline(ins,description);
    getline(ins,temp);
    ins >> dtemp;
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
      case 1:
        if(description=="description:"){
          description = description + " " + rotting_log;
        }else{
          description = description + "," + rotting_log;
        }
        cout << "Your " << description << endl;
        break;
      case 2:
        if(description=="description:"){
          description = description + " " + fresh_log;
        }else{
          description = description + "," + fresh_log;
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
          description = description + " " + sand;
        }else{
          description = description + "," + sand;
        }
        cout << "Your " << description << endl;
        break;
      case 5:
        if(description=="description:"){
          description = description + " " + dirt;
        }else{
          description = description + "," + dirt;
        }
        cout << "Your " << description << endl;
        break;
      case 6:
        if(description=="description:"){
          description = description + " " + dead_leaves;
        }else{
          description = description + "," + dead_leaves;
        }
        cout << "Your " << description << endl;
        break;
      case 7:
        if(description=="description:"){
          description = description + " " + flowers;
        }else{
          description = description + "," + flowers;
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
}


#endif
