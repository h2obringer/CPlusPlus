//************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
//
// Class: CS444
// Project: vos
// File: my_utilities.h
//
// Description: This is the header file for the
//   project wide utility functions that do the 
//   clean up, compression, and handling of certain
//   situations.
//************************************************

#ifndef MY_UTILITIES_H
#define MY_UTILITIES_H

#include <arpa/inet.h> //for ntohs() function
#include <stdio.h>
#include <vrouter.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "filter.h"
#include "print.h"
#include "create.h"
#include "structure.h"
#include <iostream>
using std::cout;
using std::endl;

//***********************************************
// Function: make_link_local_address() - create
//      the link local address for an interface
//
// Arguments - link_local_address - the place to hold the address
//	myLanList - the holder of the ethernet data for an interface
//           that we will make the address from
//***********************************************
void make_link_local_address(struct ip_v6_total_address &link_local_address, lanlist* myLanList);

//***********************************************
// Function: make_simple_address() - store a given ipv6 address
//      in a more convenient container for ease of comparison
//      later on.
//
// Arguments - address - the address to make more convenient
//	container - the place to store the convenient address
//***********************************************
void make_simple_address(char* tempBuff, struct ip_v6_total_address &address, std::string &container);

//***********************************************
// Function: condense_ethernet_address() -store a given ethernet
//      address in a more convenient container for ease of comparison
//
// Arguments - address_holder - the place to hold the convenient address
//	myLanList - the holder of the ethernet address
//***********************************************
void condense_ethernet_address(lanlist* myLanList, struct ethernet_header &address_holder);

//***********************************************
// Function: handle_router_advertisements() - retrieves
//      an interface's global ipv6 address from router 
//      advertisement packets.
//
// Arguments - tempBuff - the character buffer to store
//           simplified addresses.
//	peth - use to extract the ipv6 packet type
//      packetHolder - contains the raw packet data
//      global_address - place to store the global ipv6
//           address for an interface.
//      address_determined - edit if a global
//          address has been specified for an interface
//      my_global - simplified ipv6 global address.
//      i - the interface we are using
//***********************************************
void handle_router_advertisements(char* tempBuff, struct ethr_header* peth, void* packetHolder,
	struct ip_v6_total_address global_address, int &address_determined, std::string &my_global, int i);

//***********************************************
// Function: handle_neighbor_solicitations() - send
//      neighbor advertisements in response to 
//      neighbor solicitations.
//
// Arguments - tempBuff - the character buffer to store
//           simplified addresses.
//	peth - use to extract the ipv6 packet type
//      packetHolder - contains the raw packet data
//      global_address - place to store the global ipv6
//           address for an interface.
//      address_holder - used to put ethernet address
//           in our created packet.
//      my_global - simplified ipv6 global address.
//      my_local - simplified ipv6 link local address. 
//      debug - is debug on or off?
//      interfaceHolder - interface to send packet onto.
//***********************************************
void handle_neighbor_solicitations(char* tempBuff, struct ethr_header* peth, void* packetHolder, std::string my_local,
	std::string my_global, struct ip_v6_total_address global_address, struct ethernet_header address_holder,
	int &sizeOfPacket, int &debug, INTERFACE* interfaceHolder);

//***********************************************
// Function: handle_echo_requests() - send echo
//      replies in response to echo requests.
//
// Arguments - tempBuff - the character buffer to store
//           simplified addresses.
//	peth - use to extract the ipv6 packet type
//      packetHolder - contains the raw packet data
//      my_global - simplified ipv6 global address.
//      my_local - simplified ipv6 link local address. 
//      global_address - place to store the global ipv6
//           address for an interface.
//      address_holder - used to put ethernet address
//           in our created packet.
//      sizeOfPacket - size of the packet to send
//      debug - is debug on or off?
//      interfaceHolder - interface to send packet onto.
//***********************************************
void handle_echo_requests(char* tempBuff,struct ethr_header* peth,void* packetHolder,std::string my_local,
	std::string my_global,struct ip_v6_total_address global_address,struct ethernet_header address_holder,
	int &sizeOfPacket,int &debug,INTERFACE* interfaceHolder);

//***********************************************
// Function: handle_time_exceeded_errors() - send time
//      exceeded errors in response to hop limits reaching
//      0 and the packet is not for us when it has reached 0.
//
// Arguments - peth - use to extract the ipv6 packet type
//      packetHolder - contains the raw packet data 
//      link_local_address - place to store the link local ipv6
//           address for an interface.
//      address_holder - used to put ethernet address
//           in our created packet.
//      sizeOfPacket - size of the packet to send
//      hopCount - the hop count to examine
//      hopTest - determine whether to handle the packet later or not
//      is_router - are we a router?
//      debug - is debug on or off?
//      interfaceHolder - interface to send packet onto.
//***********************************************
void handle_time_exceeded_errors(struct ethr_header* peth,void* packetHolder,
	struct ip_v6_total_address link_local_address,struct ethernet_header address_holder,
	int &sizeOfPacket,int &debug,int &hopCount,int &hopTest,int &is_router,INTERFACE* interfaceHolder);

//***********************************************
// Function: handle_router_responsibilities() - 
//      create periodic router advertisements 
//      and other packets required periodically by
//      the router
//
// Arguments - rt - the pointer to the routing table for creating
//           multicast RIPng packets 
//      packetHolder - contains the raw packet data
//      link_local_address - place to store the link local ipv6
//           address for an interface.
//      address_holder - used to put ethernet address
//           in our created packet.
//      sizeOfPacket - size of the packet to send
//      debug - is debug on or off?
//      interfaceHolder - interface to send packet onto.
//***********************************************
void handle_router_responsibilities(struct routing_table* rt,void* packetHolder,struct ip_v6_total_address link_local_address,
	struct ethernet_header address_holder,int &sizeOfPacket,int &debug,INTERFACE* interfaceHolder);

//***********************************************
// Function: send_neighbor_discovery_packets() - 
//      build and send neighbor discovery packets
//
// Arguments - packetHolder - contains the raw packet data
//      link_local_address - place to store the link local ipv6
//           address for an interface.
//      address_holder - used to put ethernet address
//           in our created packet.
//      sizeOfPacket - size of the packet to send
//      debug - is debug on or off?
//      interfaceHolder - interface to send packet onto.
//***********************************************
void send_neighbor_discovery_packets(void* packetHolder,struct ip_v6_total_address link_local_address,
	struct ethernet_header address_holder,int &sizeOfPacket,int &debug,INTERFACE* interfaceHolder);

//***********************************************
// Function: handle_udp_echo() - send udp echo
//      replies in response to udp echo requests.
//
// Arguments - tempBuff - the character buffer to store
//           simplified addresses.
//	peth - use to extract the ipv6 packet type
//      packetHolder - contains the raw packet data
//      my_global - simplified ipv6 global address.
//      my_local - simplified ipv6 link local address. 
//      global_address - place to store the global ipv6
//           address for an interface.
//      address_holder - used to put ethernet address
//           in our created packet.
//      sizeOfPacket - size of the packet to send
//      debug - is debug on or off?
//      interfaceHolder - interface to send packet onto.
//***********************************************
void handle_udp_echo(char* tempBuff,struct ethr_header* peth,void* packetHolder,struct 
	ip_v6_total_address global_address,std::string my_local,std::string my_global,
	struct ethernet_header address_holder,int &sizeOfPacket,int &debug,INTERFACE* interfaceHolder);

//***********************************************
// Function: recieve_RIPng_packets() - build our routing 
//      table structure from RIPng packets. Does not account for duplicates
//
// Arguments - rt - pointer to our routing table to edit
//	peth - use to extract the ipv6 packet type
//      sizeOfPacket - size of the packet to send
//***********************************************
void recieve_RIPng_packets(struct routing_table* rt,struct ethr_header* peth,void* packetHolder,int &sizeOfPacket,int &debug);

#endif
