//Author: Randy Obringer
//
//File: dvd.h
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
  string get_title()const{return title;}		//Accessor functions - Helpful for
  int get_year()const{return year;}			//getting a single piece of data from 
  int get_run_time()const{return run_time;}		//a specific dvd.
  string get_movie_type()const{return movie_type;}	//
  string get_rating()const{return rating;}		//
private:
  string title;
  int year;
  int run_time;
  string movie_type;
  string rating;
};
istream& operator>>(istream& ins, dvd& temp); 	//Helpful for use from library.cc
ostream& operator<<(ostream &outs, dvd& temp);	//Helpful for use form library.cc

/*
  string temp;
  if(in==ins){	
    getline(in,temp);
    if(in.eof())return;
    title=temp;
  }
  if(in==cin){cout << "Title:\n";}
  getline(in,title);
  if(in==cin){cout << "Year:\n";}
  cin >> year;
  if(in==cin){cout << "Run time:\n";}
  cin >> run_time;
  if(in.peek()=='\n')
    in.ignore();
  if(in==cin){cout << "Movie type:\n";}
  getline(in,movie_type);
  if(in==cin){cout << "Rating:\n";}
  getline(in,rating);
  if(in==cin){cout << endl;}
  if(!in.eof()){
    getline(in,temp);
  }*/



#endif
