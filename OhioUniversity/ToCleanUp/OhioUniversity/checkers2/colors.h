//***********************************************************
//
//  File:     colors.h
//
//  Author:   Matthew Beldyk
//  Email:    mb245002@ohiou.edu
//
//  Usage:    I created this file to house some names string
//            constants with escape codes for colors in them
//            this makes it much easier for me to do colors.
//            I can still use the codes if I want, but this
//            works too.  try the statement:
//            cout<<BLUE<<"I like cookies"<<endl;
//
//		  You may use this whereever you want, but if you
//		  make any large improvements or whatever, I am
//		  curious, so email 'em my way, please.
//
//***********************************************************
//
//  all credit given to Matthew Beldyk for writing this file
//  he gave me permission to try out in my programs
//  just wanted to use to make everything look nice
//
//***********************************************************
//  I, Randy Obringer, have combined some of the strings for
//  the purposes of making checkers easier to code.
//  They are available at the end of this file.
//
//***********************************************************

#ifndef COLORS_H
#define COLORS_H

#include <string>
using namespace std;

const string BLINK     = "\e[5m";          //don't use this your
					   //professor will probibly
					   //beat you to death if
					   //you do feel the need to
					   //use blink!!!
const string BOLD      = "\e[1m";

const string RESET     = "\e[0m";
const string ERROR     = "\e[1;41;37m\a";
const string MENU       = "\e[44;37m";

const string BLACK      = "\e[30m";
const string RED        = "\e[31m";
const string GREEN      = "\e[32m";
const string YELLOW     = "\e[33m";
const string BLUE       = "\e[34m";
const string MAGENTA    = "\e[35m";
const string CYAN       = "\e[36m";
const string WHITE      = "\e[37m";

const string B_BLACK    = "\e[40m";
const string B_RED      = "\e[41m";
const string B_GREEN   = "\e[42m";
const string B_YELLOW  = "\e[43m";
const string B_BLUE    = "\e[44m";
const string B_MAGENTA = "\e[45m";
const string B_CYAN    = "\e[46m";
const string B_WHITE   = "\e[47m";

//ADDING MY OWN PIECES HERE OF CHECKERS HERE
const string RED_PIECE=B_BLACK+BOLD+RED+" O "+RESET; //red piece
const string BLACK_PIECE=B_BLACK+BOLD+WHITE+" O "+RESET; //black piece
const string RED_KING=B_BLACK+RED+BOLD+" K "+RESET; //red king
const string BLACK_KING=B_BLACK+WHITE+BOLD+" K "+RESET; //black piece

//SPACES
const string BLACK_SPACE=B_BLACK+"   ";
const string RED_SPACE=B_RED+"   ";

#endif //COLORS_H

