//*********************************************************************
//
//  Program: hw3 - model a 3D solar system for Asteroid Mining game. 
//  
//  Author: Randal M. Obringer
//  Email: ro120908@ohio.edu
//
//  Professor: David M. Chelberg
//  
//  Description: This is the header file for the functions that will 
//    produce any of the on screen messages for our program.
//    Function headers in implementation file
//
//  Last Updated: 10/26/2011
//
//*********************************************************************

#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <sstream>

#include <cstdlib>
#include <stdlib.h>
//#include <unistd.h> //for unix
#include <io.h>
#include "objects.h"
#include <GL/glut.h>

#define SIZE2 5 //size of the char array used to display the score
#define SIZE3 4 //size of the char array used to display the fuel

using namespace std;

class Text{
	public:
		Text();
		void drawText(int x, int y, char *message);
		void show_score(bool &P, bool &L, int w, int h, float screen, int score, Ship &ship);
		void post_message(int w, int h, float screen );
		void pick_ship(int w, int h, float screen, Ship &ship, int choice, int choice2 );

	private:
		string convert_int_to_string(int n);
		int line_height;
		int sleep_time;
};


#endif
