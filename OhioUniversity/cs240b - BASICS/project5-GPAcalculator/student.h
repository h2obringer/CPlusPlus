//**************************************************************************************
//File: student.h
//Author: Randy Obringer
//Purpose: This is the declaration of the student class. It includes all the 
//function prototypes that are necessary to run the program. It also includes the 
//complete accessor functions for necessary data parts.
//
//Project 5
//**************************************************************************************

#ifndef STUDENT_H
#define STUDENT_H


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

struct node{ //node-consists of a data part and a link part, this is the most essential
  string course; //part of the program that goes along with this idea of programming.
  string grade;
  double hours;
  node* link;
};

class student{
  public:
    student();  //constructor
    ~student();  //destructor
    student(const student& other); //copy constructor
    student& operator=(const student& other); //overloaded assignement operator
    istream& input_student(istream& ins); //input function for basic student info
    istream& input_course_info(istream& ins);  //input for courses
    ostream& output_student(ostream& outs);  //outputs both basic student info and courses
    string get_name()const{return name;} //accessor functions
    double get_GPA()const{return GPA;} //
    string get_PID()const{return PID;} //
    void remove_course(); //delete target function
    double GPA_calc(); //calculates GPA
    void write_to_file(); //saves data for later use
    void load_from_file(istream& ins); //loads data from previous program use
  private:
    string name;
    string PID;
    double GPA;
    node* head; //holds the entire list, must be dealt with care
};

istream& operator>>(istream& in,student& temp); //prototype included so it is recognized by 
ostream& operator<<(ostream& out,student& temp); //other files

#endif
