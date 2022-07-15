//Author: Randy Obringer
//
//File: dvd.cc
//Description: This is the implementation for the dvd class.
//It gives all the necessary functions for inputing and outputing information about dvd's.
//Extremely important for the functions of the entire program.
#include "dvd.h"
using namespace std;

dvd::dvd(){
  year=run_time=0;		//constructor function
}



ostream& operator<<(ostream& outs, dvd& temp){	//overloaded output operator makes the rest of 
	temp.output_data(outs); 		//the program run smoothly and a lot more easily
	return outs; 
	} 

ostream& dvd::output_data(ostream& outs){	//Takes the given output stream and does the 
if(outs==cout){outs << "Title: ";}		//appropriate things for the given situation.
outs << title << endl;				//Allows the proper printing to screen or
if(outs==cout){outs << "Year: ";}		//writing to file.
outs << year << endl;
if(outs==cout){outs << "Run time: ";}
outs << run_time << endl;
if(outs==cout){outs << "Movie type: ";}
outs << movie_type << endl;
if(outs==cout){outs << "Rating: ";}
outs << rating << endl;
if(outs==cout){outs << endl;}
}


istream& operator>>(istream& ins, dvd& temp){ 	//overloaded input operator makes the rest of
	temp.input_data(ins); 			//the program run smoothly and a lot more easily
	return ins; 
} 


istream& dvd::input_data(istream& in){		//Takes the given input stream and gets
  if(in==cin){cout << "Title:\n";}		//data given the situation.
  getline(in,title);				//Allows the proper reading from file as well as
  if(in==cin){cout << "Year: \n";}		//takes input from the user
  in >> year;
  if(in==cin){cout << "Run time: \n";}
  in >> run_time;  
  if(in.peek()=='\n'){
    in.ignore();
  }
  if(in==cin){cout << "Movie type: \n";}
  getline(in,movie_type);
  if(in==cin){cout << "Rating: \n";}
  getline(in,rating);
  if(in==cin){cout << endl;}
  return in; 
} 
