//************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
// Coauthor: Professor Osterman (skeleton)
//
// Class: CS444
// Project: vdump
// File: filter.h
//
// Description: This is the header file for the
//   project wide functions that filter the packet's
//   source and destination hardware addresses.
//
//   Note: this does not provide prototypes for the 
//   helper functions used by the filtering function
//************************************************
#ifndef _CS544_FILTER_H
#define _CS544_FILTER_H

#include <string>

#define HEX_BASE 16 //multiplaction needed to be made to give correct hex value
#define UPPER_A 65 //upper case A (ascii value)
#define UPPER_F 70 //upper case F (ascii value)
#define LOWER_A 97 //lower case a (ascii value)
#define LOWER_F 102 //lower case f (ascii value)
#define ZERO 48 //number 0 (ascii value)
#define NINE 57 //number 9 (ascii value)
#define HEX_L 87 //number to subtract from lower case ascii value to give hex value
#define HEX_U 55 //number to subtract from upper case ascii value to give hex value
#define COLON 58 // ":" (ascii value)
#define STAR 42 // "*" (ascii value) this is our "wild-card" in our filters

struct filterHelper{
	unsigned char filtered[17];
};

int IsAlphaNum(char c);

int is_valid_filter(char* checkMe);

int is_valid_address(char* checkMe);

void convertToStandardForm(char* convertMe,unsigned char &a,unsigned char &b,unsigned char &c,unsigned char &d,unsigned char &e,unsigned char &f);

unsigned char standardize(unsigned char one);

unsigned char merge(unsigned char one,unsigned char two);

/* (Provided by Professor Osterman:)
	filter_matches will return nonzero (true) if the 'filter' argument
	matches the 'hw_addr' argument, and zero (false) otherwise.

	@param filter char* which contains the string to match.
	@param hw_addr Hardware address being tested against the filter
	@return nonzero (true) if it matches, and zero (false) otherwise
*/

int filter_matches(char* filter, const unsigned char hw_addr[6]);

#endif

