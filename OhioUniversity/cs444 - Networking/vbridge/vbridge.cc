//***************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
// Coauthor:Professor Osterman (skeleton of program)
//
// Class: CS444
// Project: vbridge
// File: bridge.cc
//
// Description: This program runs along-side vsend to provide
//   the functionality of an internet bridge. This program is meant
//   for and only for the bin machines with more than one interface.
//   These bin machines have identified as:
//         bin10100
//         bin10001
//         bin10010
//   The vsend and vdump programs should be running concurrently on one or all 
//   of the other bin machines. This will complete a virtual network.
//   
//   The bridge acts as a smart bridge and will extract the destination
//   and source addresses from packets it receives. It then stores the addresses
//   to determine where each machine is located on the network so that it 
//   may forward packets only too where they are required. Because it is a smart 
//   bridge, it also supports the moving around of machines so that a machine can 
//   always be found. It does this by deleting addresses from its log and broadcasts
//   the packet.
//   
// Input Format: Input to the program must be in the form of a string.
//   Spaces allow for seperations of the arguments. The program does its parsing
//   on the go and doesn't seperate things in a seperate data structure. 
//
// Known Bugs:
//
//***************************************************

#include <stdlib.h>
#include <iostream>
#include <vrouter.h>
#include <string>
#include <string.h>
#include "print.h"
#include "filter.h"
#include <map>
#include <time.h>
using std::map;

#define BUFFER_SIZE 1024

int main(int argc,char *argv[]){
  int i=1; //used for for-loops
  int j=1; //used for for-loops
  unsigned group = 9; //the group number we are using
  char *tempBuff=(char*)malloc(BUFFER_SIZE); /*used to aid in parsing on the 
    go (initialize so compiler doesn't complain...*/
  lanlist *myLanList; //hold the data returned by whichlans()
  unsigned char packetHolder[BUFFER_SIZE]; //hold the data from packets read from the interface
  int sizeOfPacket=1; //holds the size of the packet as returned from readpacket()
  struct ethr_header* peth; //help extract and organize data about the packets
  std::string forwardMe; //string to be logged into the map along with the timestamp
  int where=-1; //location the destination address was found at
  int came_from=-1; //location the packet came from so that packets don't get sent out on the same interface
  time_t seconds=time(NULL); //raw time data in seconds
  long int timeAllowed=15; //time allowed on table before throwing away
  long int tempTime=0; //time stamp to pair to the address
  long int timeOnTable=0; //time calculated for being on the log
  int debug=0;

/*ENSURE THE GROUP NUMBER IS SET SO WE CAN START USING THE LIBRARY*/
  for (i=1; i < argc; ++i) {
    if(strcmp(argv[i],"-g")==0){
      if(i+1<=argc){
        tempBuff=argv[i+1];
        if(isdigit(tempBuff[0])){
          group=atoi(tempBuff);
          if(group>=63){
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

/*we can now use these functions since the group is now set********/
  setgroup(group);
  myLanList=whichlans();
/******************************************************************/
  char* interfaces[myLanList->cnt]; //we can now decide how many interfaces are present
  map<std::string,long int> locationsTimes[myLanList->cnt]; //decide how many logs to create, one for each interface
  for(i=0;i<myLanList->cnt;++i){ 
    interfaces[i]=myLanList->lan->lname;
    myLanList->lan=myLanList->lan->next;
  }
  myLanList=whichlans(); //maintain the integrity of myLanList incase we need to iterate through it again.

  // look at each argument
  for (i=1; i < argc; ++i) {

    /*DEBUG OPTION*/
    if(strcmp(argv[i],"-d")==0){
      if(setenv("VROUTER_DEBUG","9",1)!=0){
        printf("Error setting up debugging\n");
      }
      ++debug;
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

    /*TIME ADDRESS ALLOWED ON THE ADDRESS-TO-INTERFACE BINDING TABLE OPTION*/
    else if(strcmp(argv[i],"-t")==0){
      if(i+1<argc){
        tempBuff=argv[i+1];
        if(isdigit(tempBuff[0])){
          timeAllowed=(long int)tempBuff;
          ++i;
        }
      }
    }

    /*PRINT ARGUMENTS OPTION*/
    else if(strcmp(argv[j],"-h")==0){ 
      printf("Vbridge help:\n\n");
      printf("Arguments for Vbridge should be given in the following form:\n");
      printf("./vbridge [-d] [-l] [-g NUM] [-t SECONDS] [-h]\n\n");
      printf("    -d: print debugging information during execution of program\n");
      printf("    -l: print a list of interfaces with the name and hardware addresses\n");
      printf("    -g NUM: set the group number to NUM for use over the internet\n");
      printf("    -t SECONDS: set the time in seconds between sending packets to SECONDS\n");
      printf("    -h: print the help screen and the arguments given to the command line\n\n");
      printf("Arguments given were:\n");
      for (j=1; j < argc; ++j) {
        printf("argv[%d]: '%s'\n", j, argv[j]);
      }
      printf("\n");
      exit(0);
    }

    /*LIST ALL INTERFACES OPTION*/
    else if(strcmp(argv[i],"-l")==0){ 
      printf("group: %d\n",group);
      myLanList=whichlans();
      for(i=0;i<myLanList->cnt;++i){
        printf("lan name: %s\n",myLanList->lan->lname);
        printf("hwaddr: %s\n",myLanList->lan->hwaddr);
        myLanList->lan=myLanList->lan->next;
      }
      
      exit(0);
    }

    /*UNRECOGNIZED ARGUMENT SO PRINT SUMMARY OF COMMAND LINE ARGUMENTS*/
    else{
      printf("UNRECOGNIZED ARGUMENT ON THE COMMAND LINE\n");
      printf("Vbridge help:\n\n");
      printf("Arguments for Vbridge should be given in the following form:\n");
      printf("./vbridge [-d] [-l] [-g NUM] [-t SECONDS] [-h]\n\n");
      printf("    -d: print debugging information during execution of program\n");
      printf("    -l: print a list of interfaces with the name and hardware addresses\n");
      printf("    -g NUM: set the group number to NUM for use over the internet\n");
      printf("    -t SECONDS: set the time in seconds between sending packets to SECONDS\n");
      printf("    -h: print the help screen and the arguments given to the command line\n\n");
      printf("Arguments given were:\n");
      for (j=1; j < argc; ++j) { 
        printf("argv[%d]: '%s'\n", j, argv[j]);
      }
      exit(0);
    }
  }
  

  INTERFACE* interfaceHolder[myLanList->cnt+1]; //when we open an interface it holds the handle to it, add 1 for NULL

  /*open the interfaces so we can start using them*/
  for(i=0;i<myLanList->cnt;++i){
    interfaceHolder[i]=openinterface(interfaces[i]);
  }
  interfaceHolder[myLanList->cnt]=NULL; //so we can properly use blockforpacket() we add NULL as last element

  peth=(ethr_header*)packetHolder; //so the compiler doesn't complain...
  map<std::string,long int>::iterator mapIt; //Iterator for our map so we can find elements quickly


  //start reading and forwarding packets
  while(1){
    blockforpacket(interfaceHolder); //allow for asynchronization
    for(i=0;i<myLanList->cnt;++i){ //check if a packet is available on any of the interfaces
      if(checkforpacket(interfaceHolder[i])==1){
        sizeOfPacket=readpacket(interfaceHolder[i],packetHolder,BUFFER_SIZE);
        peth=(ethr_header*)packetHolder;
        came_from=i; //log which interface the packet came from so we don't forward packets back to it

        /*Reformat the address for our use*/
        if(sprintf(tempBuff,"%02x:%02x:%02x:%02x:%02x:%02x\n",peth->source[0],
        peth->source[1],peth->source[2],peth->source[3],peth->source[4],peth->source[5])!=0){
          forwardMe=tempBuff;
        }

        if(locationsTimes[i].count(forwardMe)==0){//if not in the map already
          seconds=time(NULL); //give the address a timestamp
          tempTime=(long int)seconds;
          locationsTimes[i].insert(make_pair(forwardMe,tempTime)); //then add it and it's time stamp
          if(debug>0){
            printf("%s logged into map for 'eth%d'\n",tempBuff,i+1);
          }
        }
        /*Reformat the address for our use*/
        if(sprintf(tempBuff,"%02x:%02x:%02x:%02x:%02x:%02x\n",peth->dest[0],
        peth->dest[1],peth->dest[2],peth->dest[3],peth->dest[4],peth->dest[5])!=0){
          forwardMe=tempBuff;
        }

        where=-1; //default to broadcasting the packet
        for(j=0;j<myLanList->cnt;++j){ //search every interface for the destination
          mapIt=locationsTimes[j].find(forwardMe); 
          if(mapIt!=locationsTimes[j].end()){ //if you found where to send the packet
            if(debug>0){
              printf("FOUND %s logged in map for 'eth%d'\n",tempBuff,i+1);
            }
            /*see how long the packet has been logged for*/
            seconds=time(NULL);
            tempTime=(long int)seconds;
            timeOnTable=tempTime-(mapIt->second);
            if(debug>0){
              printf("Time %s has been on the map for 'eth%d' = %ld\n",tempBuff,i+1,timeOnTable);
            }
            if(timeOnTable<=timeAllowed){ //if time logged is still good then forward it there
              where=j;
            }else{ //otherwise erase it from the map
              locationsTimes[j].erase(forwardMe);
              if(debug>0){
                printf("%s has been on the map too long. It has been erased from the map.\n",tempBuff);
              }
            }
          }
        }

        /*If the packet is going to the same interface it came from*/
        if(where==came_from){ 
          //then don't forward it anywhere else
          if(debug>0){
            printf("This packet doesn't need forwarding\n");
          }
        }
        /*If you have found it where needs to be forwarded to*/
        else if(where>0){ //then send it there
          if(writepacket(interfaceHolder[where],packetHolder,sizeof(struct ethr_header))==-1){
            printf("Failed to forward a packet\n");
          }
          if(debug>0){
            printf("Forwarding only to required interface\n");
          }
        }
        /*if the destination source is not logged anywhere*/
        else if(where<0){ //then send it everywhere except where it came from
          if(debug>0){
            printf("This packet needs forwarded everywhere\n");
          }
          for(j=0;j<myLanList->cnt;++j){
            if(j!=came_from){
              if(writepacket(interfaceHolder[j],packetHolder,sizeof(struct ethr_header))==-1){
                printf("Failed to forward a packet\n");
              }
            }
          }
        }
      }
    }
  }

  /*close the interfaces when we are done with them*/
  for(i=0;i<myLanList->cnt;++i){
    closeinterface(interfaceHolder[i]);
  }

  exit(0);
}
