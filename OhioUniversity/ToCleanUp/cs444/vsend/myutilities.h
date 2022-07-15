#ifndef MYUTILITIES_H
#define MYUTILITIES_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string>

int IsAlphaNum(char c);
int is_valid_address(char* checkMe);
void convertToStandardForm(char* convertMe,unsigned char result[6]);
unsigned char standardize(unsigned char one);
unsigned char merge(unsigned char one,unsigned char two);

#endif
