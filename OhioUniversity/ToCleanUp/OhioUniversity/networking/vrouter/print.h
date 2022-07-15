//************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
// Coauthor: Professor Osterman (skeleton)
//
// Class: CS444
// Project: vdump
// File: print.h
//
// Description: This is the header file for the
//   project wide functions that print the packets
//   Note: this does not provide prototypes for the 
//   helper functions used by the printing function
//************************************************

#ifndef PRINT_H
#define PRINT_H
// definitions of the functions that print packets
#include <arpa/inet.h> //for ntohs() function
#include <stdio.h>

/*ethr_header structure to extract data with and organize it*/
struct ethr_header{
	unsigned char dest[6]; //holds the hardware destination of packets
	unsigned char source[6]; //holds the hardware source of packets
	unsigned short etype; //holds the ethernet type of the packets
	unsigned char data[40]; //holds the first 40 bytes of data in the packets
};

//***********************************************
// Function: printpacket() - print all of the data concerning the packets we
//    have read into the program. 
//
// Arguments - packetSize - the size of the packet
//	buf - holds the raw data of the packet to be printed
//	len - length of buf which is holding the data
//	peth - our struct so we can extract and organize the data
//	sf - the source filter
//	df - the destination filter
//***********************************************
void printpacket(int packetSize,unsigned char *buf, int len,struct ethr_header* peth,
	char* sf,char* df);

#endif
