//************************************************************************
//Author: Randy Obringer
//File: Parent.h
//Description: This is the parent of all the animal children classes. It
//acts as a holder for the children so that we may enter data for the
//children with ease. It allows for a diverse set of children to be input
//using pointers to the parent. These children all have different input
//and output than this class but can be input correctly by using this 
//pointer method.
//************************************************************************

#ifndef PARENT_H
#define PARENT_H

#include <iostream>
using namespace std;

class House{
  public:
    House(){description="description:";}
    virtual void output(ostream& outs)=0;
    virtual void input(istream& ins)=0;
  protected:
    string description;
};

#endif
