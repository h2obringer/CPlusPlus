//***************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
// Coauthor:Professor Osterman (skeleton of program)
//
// Class: CS444
// Project: vsend
// File: vsend.cc
//
// Description: This program runs along side vbridge and vdump to provide
//   information through packets over a virtual network. It creates packets
//   to send by receiving a destination address through the command line.
//   It gets the source address from the whichlans() function call. 
//   
// Input Format: Input to the program must be in the form of a string.
//   Spaces allow for seperations of the arguments. The program does its parsing
//   on the go and doesn't seperate things in a seperate data structure. 
//
// Known Bugs: No known bugs found yet.
//
//***************************************************

#include <stdlib.h>
#include <iostream>
#include <vrouter.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include "filter.h" 
#include "print.h" 

#define BUFFER_SIZE 1024

int main(int argc,char *argv[]){
	int i=1; //used for for-loops
	int j=1; //used for for-loops
	char *interface; //holds the interface you are using
	INTERFACE* interfaceHolder; //when we open an interface it holds the handle to it
	unsigned group = 9; //the group number we are using
	char *tempBuff=(char*)""; /*used to aid in parsing on the 
		go (initialize so compiler doesn't complain...*/
	lanlist *myLanList; //hold the data returned by whichlans()
	struct ethr_header* peth=(ethr_header*)malloc(BUFFER_SIZE); //help extract and organize data about the packets
	int count=0; //number of packets to send, if 0 then send continuously
	int address_present=0; //tell the amount of addresses given on the command line. Only one should be given.
	void* packetHolder=malloc(BUFFER_SIZE); //holds raw packet information
	unsigned int waitTime=1000000; //waittime in microseconds (1000 milliseconds)
	int debug=0;

	/*ENSURE THERE IS A DESTINATION ADDRESS*/
	for (i=1; i < argc; ++i) {
		/*MUST BE THE ADDRESS SO IF NOT THEN COMPLAIN*/
		tempBuff=argv[i];
		if(is_valid_address(tempBuff)==1){
			++address_present;
			/*FILL IN THE DESTINATION ADDRESS FOR THE PACKETS TO BE SENT*/
			convertToStandardForm(tempBuff,peth->dest[0],peth->dest[1],peth->dest[2],peth->dest[3],peth->dest[4],peth->dest[5]);
		}
	}
  
	/*COMPLAIN IF BAD ADDRESS ARGUMENTS*/
	if(address_present!=1){
		printf("\nBad Arguments concerning destination address.\n");
		printf("  Possible problems:\n");
		printf("    Too many addresses present\n");
		printf("    No address present\n");
		printf("    Invalid address given\n");
		printf("Addresses are in the form aa:bb:cc:dd:ee:ff\n\n");
		exit(0);
	}

	/*ENSURE THE GROUP NUMBER IS SET SO WE CAN START USING THE LIBRARY*/
	for (i=1; i < argc; ++i) {
		if(strcmp(argv[i],"-g")==0){
			if(i+1<=argc){
				tempBuff=argv[i+1];
				if(isdigit(tempBuff[0])){
					group=atoi(tempBuff);
					if(group>63){
						group=9;
						printf("Invalid group number. Valid group numbers are in the range 0 - 63.\nUsing default group %d\n",group);
					}
				}else{
					printf("Invalid argument for the group number.\nUsing default group %d\n",group);
				}
			}
			++i; //needed so that the number we expect isn't caught as an unrecognized argument
		}
	}
	/******************************************************************/

	/*we can now use these functions...********************************/
	setgroup(group);
	myLanList=whichlans(); //GIVE US THE VALID LANS WE CAN USE
	interface=myLanList->lan->lname; //GET OUR DEFAULT INTERFACE
	/******************************************************************/

	// look at each argument
	for (i=1; i < argc; ++i) {

		/*DEBUG OPTION*/
		if(strcmp(argv[i],"-d")==0){
			if(setenv("VROUTER_DEBUG","9",1)!=0){
				printf("Error setting up debugging\n");
			}
		}

		/*SET GROUP OPTION (already implemented)*/
		else if(strcmp(argv[i],"-g")==0){
			/*place holder so this command isn't caught 
			as an unrecognized argument later on*/
			if(i+1<argc){
				tempBuff=argv[i+1];
				if(isdigit(tempBuff[0])){
					++i;
				}
			}
		}

		/*SET INTERFACE OPTION*/
		else if(strcmp(argv[i],"-i")==0){ 
			if(i+1<argc){
				tempBuff=argv[i+1];
				myLanList=whichlans();
				for(j=0;j<myLanList->cnt;++j){
					if(strcmp(tempBuff,myLanList->lan->lname)==0){
						interface=myLanList->lan->lname;
					}else{
						printf("Invalid or no interface given. Must be 'eth1' - 'eth16'\n");
						printf("Using default interface %s\n",interface);
					}
				}
				++i;
			}
		}

		/*SEND AMOUNT OF PACKETS OPTION*/
		else if(strcmp(argv[i],"-c")==0){ 
			if(i+1<=argc){
				tempBuff=argv[i+1];
				if(isdigit(tempBuff[0])){
					count=atoi(tempBuff);
					++i;
				}
			}
		}

		/*SET DELAY BETWEEN SENDING PACKETS OPTION*/
		else if(strcmp(argv[i],"-t")==0){ 
			if(i+1<argc){
				tempBuff=argv[i+1];
				if(isdigit(tempBuff[0])){
					waitTime=atoi(tempBuff);
					++i;
				}
			}
		}

		/*UNRECOGNIZED ARGUMENT AT THE COMMAND LINE*/
		else{
			tempBuff=argv[i];
			if(is_valid_address(tempBuff)!=1){
				printf("Unrecognized argument: %s\n",argv[i]);
				printf("Arguments expected to be in the form:\n");
				printf("  ./vsend [-d] [-g NUM] [-i IFACE] [-t MSECS] [-c COUNT] aa:bb:cc:dd:ee:ff\n");
			}
		}
	}

	/*open the interface so we can start using it*/
	interfaceHolder=openinterface(interface);

	/*CREATE PACKETS TO SEND OVER THE INTERFACE*/
	/*Fill in the packet's source information*/
	peth->source[0]=merge(myLanList->lan->hwaddr[0],myLanList->lan->hwaddr[1]); 
	peth->source[1]=merge(myLanList->lan->hwaddr[3],myLanList->lan->hwaddr[4]);
	peth->source[2]=merge(myLanList->lan->hwaddr[6],myLanList->lan->hwaddr[7]);
	peth->source[3]=merge(myLanList->lan->hwaddr[9],myLanList->lan->hwaddr[10]);
	peth->source[4]=merge(myLanList->lan->hwaddr[12],myLanList->lan->hwaddr[13]);
	peth->source[5]=merge(myLanList->lan->hwaddr[15],myLanList->lan->hwaddr[16]);
  
	/*The packet's destination has already been taken care of*/

	peth->etype=htons(2048); //create the ethernet type: 0x800 (IPv4)

	/*FILL THE FIRST 40 BYTES OF DATA FOR THE PACKET*/
	std::string packetData="These are the first packets I've sent by myself over the internet";
	for(j=0;j<40;++j){
		peth->data[j]=(unsigned char)packetData[j];
	}

	packetHolder=(void*)peth; //so the compiler doesn't cry

	//start sending packets...

	printf("Using group: %d\n",group);
	printf("Using interface '%s'\n",interface);
	if(debug>0){
		printf("Time between packets is: %d\n",waitTime);
		printf("Number of packets to send is: %d\n",count);
	}

	if(count==0){ //send packets continuously
		while(1){
			if(writepacket(interfaceHolder,packetHolder,sizeof(struct ethr_header))==-1){
				printf("Failed to send packet\n");
			}
			usleep(waitTime); //delay waitTime microseconds after sending a packet
		}
	}else if(count>0){ //send 'count' number of packets
		while(count>0){
			if(writepacket(interfaceHolder,packetHolder,sizeof(struct ethr_header))==-1){
				printf("Failed to send packet\n");
			}
			usleep(waitTime); //delay waitTime microseconds after sending a packet
			--count;
		}
	}

	/*close the interface when we are done with it*/
	closeinterface(interfaceHolder);

	exit(0);
}
