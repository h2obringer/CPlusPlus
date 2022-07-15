//Author: Randy Obringer
//File: dvd.cc
//Date Last Modified: ~2011
//Description: This is the implementation for the dvd class.
//	It gives all the necessary functions for inputing and outputing information about dvd's.
//	Extremely important for the functions of the entire program.
#include "dvd.h"
using namespace std;

//constructor
dvd::dvd(){
  year=run_time=0;		
}

//overloaded output operator makes the rest of
//	the program run smoothly and a lot more easily
ostream& operator<<(ostream& outs, dvd& temp){	 
	temp.output_data(outs); 		
	return outs; 
} 

//Takes the given output stream and does the 
//	appropriate things for the given situation.
//	Allows the proper printing to screen or
//	writing to file.
ostream& dvd::output_data(ostream& outs){	
	if(outs==cout){
		outs << "Title: ";
	}		
	outs << title << endl;				
	if(outs==cout){
		outs << "Year: ";
	}		
	outs << year << endl;
	if(outs==cout){
		outs << "Run time: ";
	}
	outs << run_time << endl;
	if(outs==cout){
		outs << "Movie type: ";
	}
	outs << movie_type << endl;
	if(outs==cout){
		outs << "Rating: ";
	}
	outs << rating << endl;
	if(outs==cout){
		outs << endl;
	}
}

//overloaded input operator makes the rest of
//	the program run smoothly and a lot more easily
istream& operator>>(istream& ins, dvd& temp){ 	
	temp.input_data(ins); 			
	return ins; 
} 

//Takes the given input stream and gets
//data given the situation. takes input from the user or reads from file.
istream& dvd::input_data(istream& in){		
	if(in==cin){
		cout << "Title:\n";
	}		
	getline(in,title);				
	if(in==cin){
		cout << "Year: \n";
	}		
	in >> year;
	if(in==cin){
		cout << "Run time: \n";
		}
	in >> run_time;  
	if(in.peek()=='\n'){
		in.ignore();
	}
	if(in==cin){
		cout << "Movie type: \n";
	}
	getline(in,movie_type);
	if(in==cin){
		cout << "Rating: \n";
	}
	getline(in,rating);
	if(in==cin){
		cout << endl;
	}
	return in; 
} 
