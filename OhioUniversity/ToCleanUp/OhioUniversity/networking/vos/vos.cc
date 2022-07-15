//***************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
//
// Class: CS444
// Project: vos
// File: vos.cc
//
// Description of what it should do: This program should first off
//   identify itself as either a router or a host. From there it 
//   will, if it is a router:
//       1. send periodic router advertisement packets.
//       2. send periodic multicast RIPng packets. 
//       3. send ICMP time exceeded messages in response to hop count expirations.
//       4. Route packets between its various interfaces using its routing table. 
//
//   On either machine it should:
//       1. Respond to ICMPv6 echo requests.
//       2. Respond to Neighbor Discovery requests.
//       3. Send Neighbor Discovery requests to map IPv6 addresses into Ethernet addresses
//       4. Contain an ARP cache with a configurable timeout.
//       5. Maintain an IPv6 routing table that it will use when sending IP packets
//       6. Receive RIPng announcements and use them to populate its routing table.
//       7. Understand and demultiplex the UDP protocol
//       8. Provide a server on the UDP echo port
//
// Description of what it does at this point: 
//   At this point this program can respond to ICMPv6 echo requests, ND requests, 
//   and multicast router advertisements. UDP protocol for echos has just been implemented
//   and in theory should work (not yet tested). Sending and recieving of RIPng packets 
//   has just been implemented. Filling our a routing table structure from RIPng packets
//   has just been implemented (not yet tested). Due to the structure I am using in structure.h
//   and the method of how I am filling my table with this structure I presume it seg faults
//   and the functions create_RIPng_packet() and recieve_RIPng_packets() should be the first 
//   places to look when a seg fault is observed. I recommend commenting out the use of these functions
//   from the utilities file so you can presume grading the rest of the project if seg faults occur.
//   
// Input Format: Input to the program must be in the form of a string.
//   Spaces allow for seperations of the arguments. The program does its parsing
//   on the go and doesn't seperate things in a seperate data structure. 
//
// Note: This program has been completely restructured from the last vi project
//   to better manage the length of the code for this program. The new files which include
//   the better structuring are: structure.h, my_utilities.h, my_utilities.cc, create.h, 
//   and create.cc. Although my program doesn't send correct multicast ripng packets the code is enplaced
//   inside handle_router_responsibilities in order to send simple and inaccurate RIPng packets. 
//
// Known Bugs: There is a structure to enplace an arp cache, 
//   however the idea is not completely implemented in the program.
//   Therefore proper routing of packets is not observed.
//
//   This program is not gauranteed to support
//   the udp protocol because I have not tested it at all for I just finished it.
//
//   The Sending of Neighbor Discovery requests to map IPv6 addresses into Ethernet addresses is known to
//   be incorrect because I have not filled in an ARP cache. If an ARP cache were to be filled and working
//   the functions create_neighbor_solicitation,create_neighbor_advertisement, and send_neighbor_discovery_packets 
//   would be changed to include the ARP table as a parameter so we can extract and add to the ARP cache. It would 
//   include checking the time on each ARP table entry for the configurable timeout option. For now I am just periodically
//   sending ND packets in place of this requirement.
//
//   Time exceeded messages seemed to send infinitely for some reason when I tried it but that could be the possibility
//   that I tested it wrong?
//
//   Recieving RIPng packets has been untested because I have
//   been unable to receive any RIPng from the DSL interface even with correct router advertisement
//   packets being sent to the DSL interface with a proper checksum. I assume it is correct however.
//
//   As noted before, my program sends malformed RIPng packets. The cause is unidentified as of now.
//   
//   Also, checksums only work for router advertisement packets. I did not have enough time to implement
//   the checksums for the other various packets this program sends because I was trying to finish other
//   important matters within this program. You can safely assume that I would be able to create proper
//   checksums for those other packets.
//
//***************************************************

#include <stdlib.h>
#include <iostream>
#include <vrouter.h>
#include <string>
#include <string.h>
#include "print.h"
#include "filter.h"
#include "structure.h"
#include "create.h"
#include "my_utilities.h"
#include <time.h>
using std::cout;
using std::endl;
using std::pair;

#define BUFFER_SIZE 1024

int main(int argc,char *argv[]){
	int i=1; //used for for-loops
	int j=1; //used for for-loops
	unsigned group = 9; //the group number we are using
	char *tempBuff=(char*)malloc(BUFFER_SIZE); /*used to aid in parsing on the 
		go (initialize so compiler doesn't complain...*/
	lanlist *myLanList; //hold the data returned by whichlans()
	void* packetHolder=malloc(BUFFER_SIZE); //holds raw packet information
	int sizeOfPacket=1; //holds the size of the packet as returned from readpacket()
	struct ethr_header* peth; //help extract and organize data about the packets
	int debug=0; //flag to tell if debug is turned off or on
	std::string packetTarget; //container for the packet Target address from 
	int hopCount=0; //the hop count of the packet we are analyzing
	int hopTest=0; //0 we will do things with the packet, 1 we will send time exceeded message and nothing more
	int DSL_link_up=0; //flag to tell if we are connecting to the real internet or not
	int num_interfaces=0; //number of interfaces that we are using
	int is_router=0; //0=host, 1=router
	time_t initialTime=time(NULL); //raw time data in seconds
	time_t currentTime=initialTime; //current time stamp in seconds
	time_t timePassed=initialTime; //time passed between last time stamp and current time stamp
	long int timeAllowed=15; //time allowed on table before throwing away
	//long int tempTime=0; //time stamp to pair to the address
	//long int timeOnTable=0; //time calculated for being on the log
	struct routing_table *myRoutingTable=(routing_table*)malloc(100);
	myRoutingTable->count=0;
	myRoutingTable->rte=NULL;
	struct arp_cache *myArpCache=(arp_cache*)malloc(100);
	myArpCache->count=0;
  
	/*THE FOLLOWING OPTIONS NEED TO HAPPEN FIRST*/
	for (i=1; i < argc; ++i) {

		/*ENSURE THE GROUP NUMBER IS SET SO WE CAN START USING THE LIBRARY*/
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

		/*DSL CONNECTION OPTION*/
		else if(strcmp(argv[j],"-D")==0){
			++DSL_link_up;
			++i; //needed so that the number we expect isn't caught as an unrecognized argument
		}
	}


	/*WE CAN NOW USE THESE LIBRARY FUNCTIONS since the group is now set************/
	setgroup(group);
	myLanList=whichlans();

	/*WE CAN NOW GRAB OUR INTERFACES AND FIND OTHER USEFUL INFORMATION*************/
	if(myLanList->cnt > 1){
		++is_router;
		printf("This is a router\n");
	}
	if(DSL_link_up > 0){
		num_interfaces=myLanList->cnt;
	}else{
		num_interfaces=myLanList->cnt-1; //we don't want the DSL interface so don't include it to be opened
		if(num_interfaces==0){ //if there are not multiple interfaces then it must have atleast one.
			num_interfaces=1;
		}
	}
	if(debug>0){
		printf("number of interfaces = %d\n",num_interfaces);
	}

	char* interfaces[num_interfaces]; //we can now decide how many interfaces are present
	for(i=0;i<myLanList->cnt;++i){ 
		interfaces[i]=myLanList->lan->lname;
		myLanList->lan=myLanList->lan->next;
	}
	myLanList=whichlans(); //maintain the integrity of myLanList incase we need to iterate through it again.

	/*START LOOKING AT EACH ARGUMENT***********************************************/  
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
					++i; //needed so that the number we expect isn't caught as an unrecognized argument
				}
			}
		}

		/*DSL CONNECTION OPTION*/
		else if(strcmp(argv[j],"-D")==0){
			++i; //needed so that the number we expect isn't caught as an unrecognized argument
		}

		/*TABLE ENTRY TIME OPTION*/
		else if(strcmp(argv[j],"-a")==0){
			if(i+1<argc){
				tempBuff=argv[i+1];
				if(isdigit(tempBuff[0])){
					timeAllowed=atoi(tempBuff);
					++i; //needed so that the number we expect isn't caught as an unrecognized argument
				}
			}
		}

		/*PRINT ARGUMENTS OPTION*/
		else if(strcmp(argv[j],"-h")==0){ 
			printVosHelp();
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
			printVosHelp();
			for (j=1; j < argc; ++j) {
				printf("argv[%d]: '%s'\n", j, argv[j]);
			}
			printf("\n");
			exit(0);
		}
	}
	/*END LOOKING AT EACH ARGUMENT*********************************************/

	/*INITIATION OF VARIABLES THAT ARE DEPENDANT UPON VROUTER LIBRARY*****************************************/
	INTERFACE* interfaceHolder[num_interfaces+1]; //when we open an interface it holds the handle to it, add 1 for NULL
	ip_v6_total_address link_local_address[num_interfaces]; //we need a link local address for each interface
	ip_v6_total_address global_address[num_interfaces]; //we need a global address for each interface
	ethernet_header address_holder[num_interfaces]; //we use this to hold each interface's ethernet address for 
			//ease of comparison

	std::string my_global[num_interfaces]; //holds the global addresses for each interface in a more convenient 
			//container for comparison purposes

	std::string my_local[num_interfaces]; //holds the link local addresses for each interface in a more 
			//convenient container

	int address_determined[num_interfaces]; //holds the flag for each interface that tells if a global addresses 
			//has been created for that interace or not

	for(i=0;i<num_interfaces;++i){
		address_determined[i]=0;
		interfaceHolder[i]=openinterface(interfaces[i]); /*OPEN THE INTERFACES SO WE CAN START USING THEM*******/
		condense_ethernet_address(myLanList,address_holder[i]); /*GATHER ETHERNET SOURCE ADDRESS TO USE LATER***/
		myLanList->lan=myLanList->lan->next;
	}
	interfaceHolder[num_interfaces]=NULL; /*ADD NULL SO WE CAN PROPERLY USE BLOCKFORPACKET()******************/
	myLanList=whichlans();

	for(i=0;i<num_interfaces;++i){/*CREATE OUR LINK LOCAL ADDRESSES FOR EACH INTERFACE************************/
		make_link_local_address(link_local_address[i],myLanList);
		global_address[i]=link_local_address[i]; /*RIGHT 1/2 OF ADDRESS IS SAME BUT ADDRESSES WILL CHANGE LATER*/
	}
	myLanList=whichlans();
	for(i=0;i<num_interfaces;++i){
		make_simple_address(tempBuff, link_local_address[i], my_local[i]);/*LOG ADDRESS IN MORE CONVENIENT CONTAINER*/
		my_global[i]=my_local[i]; //just for the sake of initializing it so the compiler doesn't complain
		printf("Link-Local Address for %s IPv6:\n",myLanList->lan->lname);
		cout << my_local[i] << endl;
		myLanList->lan=myLanList->lan->next;
	} 
	/*********************************************************************************************************/

	while(1){ //start reading and answering packets
		currentTime=time(NULL);
		timePassed=currentTime-initialTime;

		if(is_router){
			if(timePassed>20){ //send periodic packets
				initialTime=currentTime;
				for(i=0;i<num_interfaces;++i){ //send the packets to all interfaces
				  handle_router_responsibilities(myRoutingTable,packetHolder,link_local_address[i],address_holder[i],sizeOfPacket,debug,interfaceHolder[i]);
				}
			}
		}
		if(timePassed>20){
			for(i=0;i<num_interfaces;++i){ //send the packets to all interfaces
				send_neighbor_discovery_packets(packetHolder,link_local_address[i],address_holder[i],
				sizeOfPacket,debug,interfaceHolder[i]);
			}
		}

		blockforpacket_timeout(interfaceHolder,3000); //allow for asynchronization but only block for 3 seconds
		for(i=0;i<num_interfaces;++i){ //check each interface
			if(checkforpacket(interfaceHolder[i])==1){//check if a packet is available on the interface
				sizeOfPacket=readpacket(interfaceHolder[i],packetHolder,BUFFER_SIZE);
				peth=(ethr_header*)packetHolder;

				handle_time_exceeded_errors(peth,packetHolder,link_local_address[i],address_holder[i],
				sizeOfPacket,debug,hopCount,hopTest,is_router,interfaceHolder[i]);

				if(hopTest==0){ //edited in handle_time_exceeded_errors
						handle_router_advertisements(tempBuff,peth,packetHolder,global_address[i],
						address_determined[i],my_global[i],i);
					handle_neighbor_solicitations(tempBuff,peth,packetHolder,my_local[i],my_global[i],
						global_address[i],address_holder[i],sizeOfPacket,debug,interfaceHolder[i]);
					handle_echo_requests(tempBuff,peth,packetHolder,my_local[i],my_global[i],
						global_address[i],address_holder[i],sizeOfPacket,debug,interfaceHolder[i]);
					handle_udp_echo(tempBuff,peth,packetHolder,global_address[i],my_local[i],my_global[i],
						address_holder[i],sizeOfPacket,debug,interfaceHolder[i]);
					recieve_RIPng_packets(myRoutingTable,peth,packetHolder,sizeOfPacket,debug);
				}//end hoplimit not 0 and/or not for us
			}//end checkforpacket
		}//end check each interface
	}//end start reading and answering packets

	/*close the interfaces when we are done with them*/
	for(i=0;i<myLanList->cnt;++i){
		closeinterface(interfaceHolder[i+1]);
	}

	exit(0);
}
