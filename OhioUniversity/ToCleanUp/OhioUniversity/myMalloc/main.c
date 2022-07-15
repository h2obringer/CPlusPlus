//************************************************************
// 	"A Re-Implementation of the Malloc Function"
// Authors: Randal Mark Obringer and Leni Austin
// School: Ohio University
// Email: ro120908@ohio.edu
//
// Class: CS442 (Operating Systems)
// Professor: Frank Drews
//
// File: main.c
// Description: demonstrate use of our implemented malloc and free functions
//
// Last Updated: 2 March 2012
//
//************************************************************
#include "mymalloc.h"
#include <stdio.h>

int main(){
	int* ptr_1=malloc(8);
	ptr_1=4;
	printf("%d\n",ptr_1);
	int* ptr_2=malloc(8);
	ptr_2=8;
	printf("%d\n",ptr_2);
	free(ptr_2);
	write(STDOUT_FILENO,"Freed ptr_2!!\n",14);
	free(ptr_1);
	write(STDOUT_FILENO,"Freed ptr_1!!\n",14);
	return 0;
}
