//***************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
// Coauthor:Professor Osterman (skeleton of program)
//
// Class: CS444
// Project: vdump
// File: vdump.cc
//
// Description: This program runs along side vr_pickup to provide
//   information on the packets being picked up on a virtual router. 
//   It allows for filtering of the destination and source hardware 
//   addresses. You man choose which interface your on, turn on debugging,
//   show the command line arguments given to the program, list the available
//   interfaces, and specify the group number you are on. 
//   
// Input Format: Input to the program must be in the form of a string.
//   Spaces allow for seperations of the arguments. The program does its parsing
//   on the go and doesn't seperate things in a seperate data structure. 
//
// Known Bugs: I have fixed many of the errors that came up from the submission
//   test programs. 
//
//***************************************************

#include <stdlib.h>
#include <iostream>
#include <vrouter.h>
#include <string>
#include <string.h>
#include "print.h"
#include "filter.h"

#define BUFFER_SIZE 1024
//static int debug = 0;

int main(int argc,char *argv[]){
  int i=1; //used for for-loops
  int j=1; //used for for-loops
  char *interface; //holds the interface you are holding
  INTERFACE* interfaceHolder; //when we open an interface it holds the handle to it
  unsigned group = 9; //the group number we are using
  char *tempBuff=(char*)""; /*used to aid in parsing on the 
    go (initialize so compiler doesn't complain...*/
  lanlist *myLanList; //hold the data returned by whichlans()
  unsigned char packetHolder[BUFFER_SIZE]; //hold the data from packets read from the interface
  int sizeOfPacket=1; //holds the size of the packet as returned from readpacket()
  struct ethr_header* peth; //help extract and organize data about the packets
  char* destFilter=(char*)"*:*:*:*:*:*"; //destination filter to apply
  char* sourceFilter=(char*)"*:*:*:*:*:*"; //source filter to apply

/*ENSURE THE GROUP NUMBER IS SET SO WE CAN START USING THE LIBRARY*/
  for (i=1; i < argc; ++i) {
    if(strcmp(argv[i],"-g")==0){
      if(i+1<argc){
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

    /*DESTINATION FILTERING OPTION*/
    else if(strcmp(argv[i],"-hwdest")==0){
      if(i+1<argc){
        if(is_valid_filter(argv[i+1])){
          destFilter=argv[i+1];
        }else{
          printf("Not a valid destination address filter. Using default filter: *:*:*:*:*:*\n");
        }
        ++i;
      }
    }

    /*SOURCE FILTERING OPTION*/
    else if(strcmp(argv[i],"-hwsource")==0){
      if(i+1<argc){
        if(is_valid_filter(argv[i+1])){
          sourceFilter=argv[i+1];
        }else{
          printf("Not a valid destination address filter. Using default filter: *:*:*:*:*:*\n");
        }
        ++i;
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

    /*SUMMARY OF COMMAND LINE ARGUMENTS OPTION*/            
    else if(strcmp(argv[j],"-h")==0){ 
      printf("Vdump help:\n\n");
      printf("Arguments for Vdump should be given in the following form:\n");
      printf("./vdump [-d] [-l] [-g NUM] [-i IFACE] [--hwsource SADDR] [--hwdest DADDR] [-h]\n\n");
      printf("    -d: print debugging information during execution of program\n");
      printf("    -l: print a list of interfaces with the name and hardware addresses\n");
      printf("    -g NUM: set the group number to NUM for use over the internet\n");
      printf("    -i IFACE: set the interface to IFACE\n");
      printf("    -hwsource SADDR: filter the source address to the specifications of SADDR\n");
      printf("    -hwdest DADDR: filter the destination address to the specifications of DADDR\n");
      printf("    -h: print the help screen and the arguments given to the command line\n\n");
      printf("Arguments given were:\n");
      for (j=1; j < argc; ++j) {
        printf("argv[%d]: '%s'\n", j, argv[j]);
      }
      exit(0);

    /*LIST ALL INTERFACES OPTION*/
    }else if(strcmp(argv[i],"-l")==0){ 
      printf("group: %d\n",group);
      myLanList=whichlans();
      for(i=0;i<myLanList->cnt;++i){
        printf("lan name: %s\n",myLanList->lan->lname);
        printf("hwaddr: %s\n",myLanList->lan->hwaddr);
        myLanList->lan=myLanList->lan->next;
      }
      exit(0);

    /*UNRECOGNIZED ARGUMENT SO PRINT SUMMARY OF COMMAND LINE ARGUMENTS*/
    }else{
      printf("UNRECOGNIZED ARGUMENT ON THE COMMAND LINE\n");
      printf("Vdump help:\n\n");
      printf("Arguments for Vdump should be given in the following form:\n");
      printf("./vdump [-d] [-l] [-g NUM] [-i IFACE] [--hwsource SADDR] [--hwdest DADDR] [-h]\n\n");
      printf("    -d: print debugging information during execution of program\n");
      printf("    -l: print a list of interfaces with the name and hardware addresses\n");
      printf("    -g NUM: set the group number to NUM for use over the internet\n");
      printf("    -i IFACE: set the interface to IFACE\n");
      printf("    -hwsource SADDR: filter the source address to the specifications of SADDR\n");
      printf("    -hwdest DADDR: filter the destination address to the specifications of DADDR\n");
      printf("    -h: print the help screen and the arguments given to the command line\n\n");
      printf("Arguments given were:\n");
      for (j=1; j < argc; ++j) { 
        printf("argv[%d]: '%s'\n", j, argv[j]);
      }
      exit(0);
    }
  }

  /*open the interface so we can start using it*/
  interfaceHolder=openinterface(interface);

  peth=(ethr_header*)packetHolder; //so the compiler doesn't complain...

  printf("Using group %d\n",group);
  printf("Using interface '%s'\n",interface);
  printf("Using source filter '%s'\n",sourceFilter);
  printf("Using destination filter '%s'\n\n",destFilter);

  //start reading and printing packets...
  while(sizeOfPacket>=0){
    sizeOfPacket=readpacket(interfaceHolder,packetHolder,BUFFER_SIZE);
    printpacket(sizeOfPacket,packetHolder,BUFFER_SIZE,peth,sourceFilter,destFilter);
  }

  /*close the interface when we are done with it*/
  closeinterface(interfaceHolder);

  exit(0);
}
