//************************************************************
// 	"A Re-Implementation of the Malloc Function"
// Authors: Randal Mark Obringer and Leni Austin
// School: Ohio University
// Email: ro120908@ohio.edu
//
// Class: CS442 (Operating Systems)
// Professor: Frank Drews
//
// File: mymalloc.h
// Description: This is the header file to my implementation
//   of malloc and other dynamic memory related functions.
//
// Last Updated: 2 March 2012
//
//************************************************************

#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <sys/types.h> //for size_t
#include <string.h> //for memcpy and memset
#include <unistd.h> //for sbrk
#include <stdlib.h> //for exit

/*PROTOTYPES*/
extern void* malloc(size_t size);
extern void free(void *ptr);
extern void* calloc(size_t nmemb, size_t size);
extern void* realloc(void *ptr, size_t size);



#endif
