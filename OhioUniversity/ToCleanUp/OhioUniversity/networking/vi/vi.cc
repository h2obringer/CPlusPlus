//***************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
//
// Class: CS444
// Project: vi
// File: vi.cc
//
// Description: This program will create its own link local IPv6 address
//   upon starting up for all of its interfaces using the specifications
//   given in the RFC's. In order for this program to create its global
//   IPv6 addresses for each interface it must receive router advertisement
//   packets from the vrad daemon program. The program will not allow the processing
//   of any packet other than a router advertisement until it has created its
//   global address.
//
//   After a global address has been created for a given interface it can start
//   receiving neighbor solicitation packets from the vping6 program and answering
//   these packets with neighbor advertisement packets. 
//
//   Once vping6 has received a neighbor advertisement from vi the expected behavior
//   should be for vping6 to send echo request packets. vi will respond by sending
//   echo replies to the vping6 program.
//   
// Input Format: Input to the program must be in the form of a string.
//   Spaces allow for seperations of the arguments. The program does its parsing
//   on the go and doesn't seperate things in a seperate data structure. 
//
// Known Bugs: After vping6 receives neighbor advertisement packets from this program
//   it will start sending echo request packets with the its source address as
//   the echo request's source and destination ethernet addresses. This prevents 
//   vi from sending echo reply packets to vping6 because there is no way of matching 
//   the packets destination address to my programs source address. For the sake of
//   showing that my echo reply packets are sent and built correctly I have commented
//   out the if statement that does this check...
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
using std::cout;
using std::endl;

#define BUFFER_SIZE 1024

int main(int argc,char *argv[]){
	int i=1; //used for for-loops
	int j=1; //used for for-loops
	int k=1; //used for for-loops
	unsigned group = 9; //the group number we are using
	char *tempBuff=(char*)malloc(BUFFER_SIZE); /*used to aid in parsing on the 
		go (initialize so compiler doesn't complain...*/
	lanlist *myLanList; //hold the data returned by whichlans()
	void* packetHolder=malloc(BUFFER_SIZE); //holds raw packet information
	int sizeOfPacket=1; //holds the size of the packet as returned from readpacket()
	struct ethr_header* peth; //help extract and organize data about the packets
	struct vrad_packet* pvrad; //extract the data of packets sent from the vrad program 
		//with the correct data segments in place

	struct neighbor_solicitation_advertisement* pvping; //extract the data from neighbor 
		//solicitation packets sent from the vping6 program with the correct 
		//data segments in place

	struct neighbor_solicitation_advertisement* pNSresponse; //aid in building a proper 
		//neighbor advertisement packet

	struct echo_request_reply* perequest; //extract the data from echo request packets sent
		//sent from the vping6 program with the correct data segments in place

	struct echo_request_reply* pereply; //aid in building a proper echo reply packet
	int debug=0; //flag to tell if debug is turned off or on
	unsigned char modifier=2; //used to perform bitwise operations for the link local address 
		//and the global address

	std::string packetTarget; //container for the packet Target address from 

	/*The following assigments are made so the compiler doesn't complain...*/
	pvrad=(struct vrad_packet*)packetHolder; 
	pvping=(struct neighbor_solicitation_advertisement*)packetHolder; 
	pNSresponse=(struct neighbor_solicitation_advertisement*)packetHolder;
	perequest=(struct echo_request_reply*)packetHolder;
	pereply=(struct echo_request_reply*)packetHolder;
	/***********************************************************************/

  
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

	/*WE CAN NOW USE THESE LIBRARY FUNCTIONS since the group is now set now********/
	setgroup(group);
	myLanList=whichlans();
	/******************************************************************************/

	/*WE CAN NOW GRAB OUR INTERFACES***********************************************/
	char* interfaces[myLanList->cnt]; //we can now decide how many interfaces are present
	for(i=0;i<myLanList->cnt;++i){ 
		interfaces[i]=myLanList->lan->lname;
		myLanList->lan=myLanList->lan->next;
	}
	myLanList=whichlans(); //maintain the integrity of myLanList incase we need to iterate through it again.
	/******************************************************************************/

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
					++i;
				}
			}
		}

		/*PRINT ARGUMENTS OPTION*/
		else if(strcmp(argv[j],"-h")==0){ 
			printf("Vi help:\n\n");
			printf("Arguments for Vi should be given in the following form:\n");
			printf("./vi [-d] [-l] [-g NUM] [-h]\n\n");
			printf("    -d: print debugging information during execution of program\n");
			printf("    -l: print a list of interfaces with the name and hardware addresses\n");
			printf("    -g NUM: set the group number to NUM for use over the internet\n");
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
			printf("Vi help:\n\n");
			printf("Arguments for Vi should be given in the following form:\n");
			printf("./vi [-d] [-l] [-g NUM] [-h]\n\n");
			printf("    -d: print debugging information during execution of program\n");
			printf("    -l: print a list of interfaces with the name and hardware addresses\n");
			printf("    -g NUM: set the group number to NUM for use over the internet\n");
			printf("    -h: print the help screen and the arguments given to the command line\n\n");
			printf("Arguments given were:\n");
			for (j=1; j < argc; ++j) { 
				printf("argv[%d]: '%s'\n", j, argv[j]);
			}
			exit(0);
		}
	}
	/*END LOOKING AT EACH ARGUMENT*********************************************/


	/*INITIATION OF VARIABLES THAT ARE DEPENDANT UPON VROUTER LIBRARY*/
	INTERFACE* interfaceHolder[myLanList->cnt+1]; //when we open an interface it holds the handle to it, add 1 for NULL
	ip_v6_total_address link_local_address[myLanList->cnt]; //we need a link local address for each interface
	ip_v6_total_address global_address[myLanList->cnt]; //we need a global address for each interface
	ethernet_header address_holder[myLanList->cnt]; //we use this to hold each interfaces ethernet address for 
			//ease of comparison

	std::string my_global[myLanList->cnt]; //holds the global addresses for each interface in a more convenient 
			//container for comparison purposes

	std::string my_local[myLanList->cnt]; //holds the link local addresses for each interface in a more 
			//convenient container

	int address_determined[myLanList->cnt]; //holds the flag for each interface that tells if a global addresses 
			//has been created for that interace or not

	/*OPEN THE INTERFACES SO WE CAN START USING THEM, ALSO GATHER OUR ETHERNET SOURCE ADDRESSE SO WE CAN CREATE
	PACKETS CORRECTLY LATER ON*/
	for(i=0;i<myLanList->cnt;++i){
		address_determined[i]=0;
		interfaceHolder[i]=openinterface(interfaces[i]);
		address_holder[i].source[0]=merge(myLanList->lan->hwaddr[0],myLanList->lan->hwaddr[1]); 
		address_holder[i].source[1]=merge(myLanList->lan->hwaddr[3],myLanList->lan->hwaddr[4]);
		address_holder[i].source[2]=merge(myLanList->lan->hwaddr[6],myLanList->lan->hwaddr[7]);
		address_holder[i].source[3]=merge(myLanList->lan->hwaddr[9],myLanList->lan->hwaddr[10]);
		address_holder[i].source[4]=merge(myLanList->lan->hwaddr[12],myLanList->lan->hwaddr[13]);
		address_holder[i].source[5]=merge(myLanList->lan->hwaddr[15],myLanList->lan->hwaddr[16]);
		myLanList->lan=myLanList->lan->next;
	}
	interfaceHolder[myLanList->cnt]=NULL; //so we can properly use blockforpacket() we add NULL as last element
	myLanList=whichlans();
	/**********************************************************************************************************/
  
  /*CREATE OUR LINK LOCAL ADDRESSES FOR EACH INTERFACE*******************************************************/
	for(i=0;i<myLanList->cnt;++i){
		//create the linklocal prefix portion (FE80:0000:0000:0000)
		link_local_address[i].total_address[0]=254; //FE
		link_local_address[i].total_address[1]=128; //80
		link_local_address[i].total_address[2]=0; //00
		link_local_address[i].total_address[3]=0; //00
		link_local_address[i].total_address[4]=0; //00
		link_local_address[i].total_address[5]=0; //00
		link_local_address[i].total_address[6]=0; //00
		link_local_address[i].total_address[7]=0; //00

		//fill in the ethernet address portion by splitting the ethernet address in half and adding FFFE in the middle
		k=8; //keeps track of where we are in filling in our link local address
		j=0; //keeps track of where we are on our ethernet address for when we are breaking it appart
		while(k<16){
			if(k==11){//add FFFE in the appropriate spots
				link_local_address[i].total_address[k]=255; //FF
			}else if(k==12){
				link_local_address[i].total_address[k]=254; //FE
			}else{
				link_local_address[i].total_address[k]=merge(myLanList->lan->hwaddr[j],myLanList->lan->hwaddr[j+1]);
				if(k==8){ //if its the first octet in the second half of the address

					//flip the second to lowest order bit
					if((link_local_address[i].total_address[k]&modifier)==2){ 
						link_local_address[i].total_address[k]-=2;
					}else{
						link_local_address[i].total_address[k]+=2;
					}
				}
				j=j+3; //increase to the next unused portion of the address from hwaddr in myLanList
			}
			++k; //move on to the next portion of our link-local address to fill in
		}
		global_address[i]=link_local_address[i]; //right half of address will be the same although we expect other half to change
	}
	/*END CREATE LINK LOCAL ADDRESSES FOR EACH INTERFACE*******************************************************/

	/*LOG OUR LINK LOCAL ADDRESSES IN A MORE CONVENIENT CONTAINER FOR COMPARISON PURPOSES LATER AND PRINT IT OUT*/
	for(i=0;i<myLanList->cnt;++i){
		sprintf(tempBuff,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",link_local_address[i].
		total_address[0],link_local_address[i].total_address[1],link_local_address[i].total_address[2],
		link_local_address[i].total_address[3],link_local_address[i].total_address[4],link_local_address[i].
		total_address[5],link_local_address[i].total_address[6],link_local_address[i].total_address[7],
		link_local_address[i].total_address[8],link_local_address[i].total_address[9],link_local_address[i].
		total_address[10],link_local_address[i].total_address[11],link_local_address[i].total_address[12],
		link_local_address[i].total_address[13],link_local_address[i].total_address[14],link_local_address[i].
		total_address[15]);
		my_local[i]=tempBuff;
		my_global[i]=tempBuff; //just for the sake of initializing it so the compiler doesn't complain
	  
		printf("Link-Local Address for eth%d IPv6:\n",i+1);
		cout << my_local[i] << endl;
	} 
	/*************************************************************************************************************/
  
	while(1){ //start reading and answering packets
		blockforpacket(interfaceHolder); //allow for asynchronization
		for(i=0;i<myLanList->cnt;++i){ //check each interface
			if(checkforpacket(interfaceHolder[i])==1){//check if a packet is available on the interface
				sizeOfPacket=readpacket(interfaceHolder[i],packetHolder,BUFFER_SIZE);
				peth=(ethr_header*)packetHolder;
				
				/*IF PACKET IS A ROUTER ADVERTISEMENT (type 0x86)*/
				if(peth->data[40]==134){ 
					pvrad=(vrad_packet*)packetHolder; //structure it properly
					for(j=0;j<8;++j){ //grab the rest of our local address from the prefix option
						global_address[i].total_address[j]=pvrad->po.prefix[j];
					}
					address_determined[i]=1; //set the flag that we have our global address for this interface

					//put the address in a more convenient container
					sprintf(tempBuff,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",global_address[i].
						total_address[0],global_address[i].total_address[1],global_address[i].total_address[2],
						global_address[i].total_address[3],global_address[i].total_address[4],global_address[i].
						total_address[5],global_address[i].total_address[6],global_address[i].total_address[7],
						global_address[i].total_address[8],global_address[i].total_address[9],global_address[i].
						total_address[10],global_address[i].total_address[11],global_address[i].total_address[12],
						global_address[i].total_address[13],global_address[i].total_address[14],global_address[i].
						total_address[15]);
					my_global[i]=tempBuff;

					//finally print it out
					printf("Global Address for eth%d IPv6\n",i+1);
					cout << my_global[i] << endl;
				}//end packet is a router advertisement (type 0x86)

				/*IF WE HAVE A GLOBAL ADDRESS FOR THIS INTERFACE*/
				if(address_determined[i]==1){
					/*IF ETHERNET DESTINATION IS MULTICAST*/
					if((peth->dest[0]==255)&&(peth->dest[1]==255)&&(peth->dest[2]==255)&&(peth->dest[3]==255)&&
						(peth->dest[4]==255)&&(peth->dest[5]==255)){
						if(debug>0){
							printf("Ethernet destination is multicast\n");
						}
						/*IF PACKET IS A NEIGHBOR SOLICITATION (type 0x87)*/
						if(peth->data[40]==135){
							if(debug>0){
								printf("The packet is a Neighbor solicitation\n");
							}
							pvping=(neighbor_solicitation_advertisement*)packetHolder; //structure it properly

							//store target address in a more convenient container for comparison
							if(sprintf(tempBuff,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
								pvping->target_address[0],pvping->target_address[1],pvping->target_address[2],pvping->
								target_address[3],pvping->target_address[4],pvping->target_address[5],pvping->
								target_address[6],pvping->target_address[7],pvping->target_address[8],pvping->target_address[9],pvping->
								target_address[10],pvping->target_address[11],pvping->target_address[12],pvping->
								target_address[13],pvping->target_address[14],pvping->target_address[15])!=0){
								packetTarget=tempBuff; 
							}
						   
							/*IF TARGET ADDRESS IS OUR LINK LOCAL OR GLOBAL ADDRESS*/
							if((packetTarget==my_local[i])||(packetTarget==my_global[i])){
								//create a neighbor advertisement packet in response to the neighbor solicitation packet
								create_neighbor_advertisement(address_holder[i],global_address[i],pvping,pNSresponse); 
								packetHolder=(void*)pNSresponse;
								if(writepacket(interfaceHolder[i],packetHolder,sizeof(struct neighbor_solicitation_advertisement))==-1){
									printf("Failed to send a neighbor advertisement\n");
								}else{
									if(debug>0){
										printf("Neighbor Advertisement sent in reply to the Neighbor Solicitation\n");
									}
								}
							}//end target addres is link local or global address
						}//end neighbor solicitation (type 0x87)
					}//end multicast ethernet destination

					/*IF ETHERNET DESTINATION OF AN ECHO REQUEST IS OUR ETHERNET ADDRESS */
					//if((address_holder[i].source[0]==peth->dest[0])&&(address_holder[i].source[1]==peth->dest[1])
					//&&(address_holder[i].source[2]==peth->dest[2])&&(address_holder[i].source[3]==peth->dest[3])
					//&&(address_holder[i].source[4]==peth->dest[4])&&(address_holder[i].source[5]==peth->dest[5])){
					/*IF ETHERNET TYPE IS IPV6 (type 0x86dd)*/
					if(ntohs(peth->etype)==34525){
						if(debug>0){
							printf("Ethernet type = IPv6 (0x86dd)\n");
						}
						perequest=(echo_request_reply*)packetHolder; //structure it properly
						//store the packet ipv6 destination in a more convenient container for comparison purposes
						if(sprintf(tempBuff,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
							perequest->v6_dest[0],perequest->v6_dest[1],perequest->v6_dest[2],perequest->v6_dest[3],
							perequest->v6_dest[4],perequest->v6_dest[5],perequest->v6_dest[6],perequest->v6_dest[7],
							perequest->v6_dest[8],perequest->v6_dest[9],perequest->v6_dest[10],perequest->v6_dest[11],
							perequest->v6_dest[12],perequest->v6_dest[13],perequest->v6_dest[14],perequest->v6_dest[15])!=0){
							packetTarget=tempBuff;
						}
						/*IF IPV6 DESTINATION IS EITHER OUR LINK LOCAL OR GLOBAL ADDRESS*/
						if((my_local[i]==packetTarget)||(my_global[i]==packetTarget)){
							if(debug>0){
								printf("The target address is meant for us\n");
							}
							/*IF PACKET IS AN ECHO REQUEST (type 0x80)*/
							if(peth->data[40]==128){ //if echo request
								if(debug>0){
									printf("This packet is an echo request\n");
								}
								//create an echo reply packet in response to an echo request packet
								create_echo_reply(address_holder[i],global_address[i],perequest,pereply);
								packetHolder=(void*)pereply;
								if(writepacket(interfaceHolder[i],packetHolder,sizeof(struct echo_request_reply))==-1){
									printf("Failed to send an echo reply\n");
								}else{
									if(debug>0){
										printf("Echo Reply sent in reply to the Echo Request\n");
									}
								}
							}//end if echo request
						}//end ipv6 destination is link local or global address
					}//end ethernet type is ipv6 (0x86dd)
				  //}//end ethernet destination of an echo request is our ethernet address
				}//end if global address is present for the interface
			}//end check if a packet is available on the interface
		}//end check each interface
	}//end reading and answering packets

	/*close the interfaces when we are done with them*/
	for(i=0;i<myLanList->cnt;++i){
		closeinterface(interfaceHolder[i]);
	}

	exit(0);
}
