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
//   Also included are defined statements
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
#define MIN_ADDR_SIZE 11 //minimum allowable address size
#define MOST_IN_SECTION 2 //max amount of characters within a section of the address
#define LEAST_IN_SECTION 1 //least amount of character within a section of the address 

struct filterHelper{
	unsigned char filtered[17];
};

int IsAlphaNum(char c);

int is_valid_filter(char* checkMe);

int is_valid_address(char* checkMe);

void convertToStandardForm(char* convertMe,unsigned char &a,unsigned char &b,unsigned char &c,unsigned char &d,unsigned char &e,unsigned char &f);

unsigned char standardize(unsigned char one);

unsigned char merge(unsigned char one,unsigned char two);

int filter_matches(char* filter, const unsigned char hw_addr[6]);

#endif

