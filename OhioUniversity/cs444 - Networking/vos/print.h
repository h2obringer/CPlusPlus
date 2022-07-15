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
//   as well as the functions that structure packets
//   to be sent. It contains the structure definations 
//   used throughout the projects
//************************************************

#ifndef PRINT_H
#define PRINT_H

#include <arpa/inet.h> //for ntohs() function
#include <stdio.h>
#include <vrouter.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "structure.h"

//***********************************************
// Function: printRoutingTable() - print the contents
//      of our routing table. (all the entries we have)
//
// Arguments: rt - the pointer to our routing table.
//
//***********************************************
void printRoutingTable(struct routing_table* rt);

//***********************************************
// Function: printVosHelp() - print the help message
//      for our program.
//***********************************************
void printVosHelp();

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
