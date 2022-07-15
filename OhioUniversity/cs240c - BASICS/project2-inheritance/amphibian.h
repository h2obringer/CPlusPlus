//************************************************************************
//Author: Randy Obringer
//File: Amphibian.h
//Description: This is a child of the House class.
//It inherits the input and output functions as well as the string called
//description. It veries slightly from all the other children.
//************************************************************************
//COMPLETE!!!!!
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
    string lillipad,rock,dirt,grass,sand,cylinder,rectangle,temp,name;
    double radius,height,width,dtemp;
};

Amphibian::Amphibian(){
  lillipad="lillipad"; rock="rock"; sand="sand";
  dirt="dirt"; grass="grass";name="Amphibian ||";
  cylinder="in a cylindrical tank "; rectangle="in a rectangular tank "; temp="";
  radius=height=width=dtemp=0.0;
}

void Amphibian::output(ostream& outs){
  if(outs==cout){
    outs << name << " " << description << " " << temp << "with an area of " << dtemp << endl;
  }else{
    outs << name << endl;
    outs << description << endl;
    outs << temp << endl;
    outs << dtemp << endl;
  }
}

void Amphibian::tank(string s){
  temp=s;
}

void Amphibian::Rarea(double d1,double d2){
  dtemp=d1*d2;
}

void Amphibian::Carea(double d1,double d2){
  dtemp=3.14*d1*d1*d2;
}

void Amphibian::input(istream& ins){
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
    }     
  }else{
    getline(ins,description);
    getline(ins,temp);
    ins >> dtemp;
  }
}

void Amphibian::input2(){ //my form of input
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
      case 1:
        if(description=="description:"){
          description = description + " " + lillipad;
        }else{
          description = description + "," + lillipad;
        }
        cout << "Your " << description << endl;
        break;
      case 2:
        if(description=="description:"){
          description = description + " " + rock;
        }else{
          description = description + "," + rock;
        }
        cout << "Your " << description << endl;
        break;
      case 3:
        if(description=="description:"){
          description = description + " " + dirt;
        }else{
          description = description + "," + dirt;
        }
        cout << "Your " << description << endl;
        break;
      case 4:
        if(description=="description:"){
          description = description + " " + grass;
        }else{
          description = description + "," + grass;
        }
        cout << "Your " << description << endl;
        break;
      case 5:
        if(description=="description:"){
          description = description + " " + sand;
        }else{
          description = description + "," + sand;
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
