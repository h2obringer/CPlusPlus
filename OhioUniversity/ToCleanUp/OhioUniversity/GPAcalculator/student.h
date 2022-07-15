//**************************************************************************************
//File: student.h
//
//Author: Randy Obringer
//
//Date Last Modified: ~2010
//
//Purpose: This is the declaration of the student class and course node structure.
//**************************************************************************************

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

//a course node that implements a linked list
struct node{
	string course;
	string grade;
	double hours;
	node* link;
};

class student{
	public:
		student();  //constructor
		~student();  //destructor
		student(const student& other); 				//copy constructor
		student& operator=(const student& other); 	//overloaded assignement operator
		istream& input_student(istream& ins); 		//input function for basic student info
		istream& input_course_info(istream& ins);  	//input for courses
		ostream& output_student(ostream& outs);  	//outputs both basic student info and courses
		//accessor functions
		string get_name()const{return name;}
		double get_GPA()const{return GPA;}
		string get_PID()const{return PID;}
		
		void remove_course(); //delete course specified by user
		double GPA_calc(); //calculates GPA of the student
		void write_to_file(); //saves data to file for later use
		void load_from_file(istream& ins); //loads data from file from previous program use
	private:
		string name;
		string PID;
		double GPA;
		node* head; //holds the entire list, must be dealt with care
};

istream& operator>>(istream& in,student& temp); //prototype included so it is recognized by other files
ostream& operator<<(ostream& out,student& temp); 

#endif
