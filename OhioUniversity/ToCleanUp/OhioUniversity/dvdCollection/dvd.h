//Author: Randy Obringer
//File: dvd.h
//Date Last Modified: ~2011 
//Description: This is the header file for the dvd class. Allows the other files to see all the 
//functions necessary for completing the task of the entire program.
//

#ifndef dvd_h
#define dvd_h

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class dvd{
	public:
		dvd();
		ostream& output_data(ostream& outs);
		istream& input_data(istream& ins); 
		//Accessor functions
		string get_title()const{return title;}		
		int get_year()const{return year;}			
		int get_run_time()const{return run_time;}		
		string get_movie_type()const{return movie_type;}	
		string get_rating()const{return rating;}		
	private:
		string title;
		int year;
		int run_time;
		string movie_type;
		string rating;
};

istream& operator>>(istream& ins, dvd& temp); 	//Helpful for use in library.cc
ostream& operator<<(ostream &outs, dvd& temp);	//Helpful for use in library.cc

#endif
