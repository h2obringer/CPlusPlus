//************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
//
// Class: CS444
// Project: vos
// File: create.h
//
// Description: This is the header file for the
//   project wide functions that actually build
//   the packets that we are required to send.
//************************************************
#ifndef CREATE_H
#define CREATE_H

#include <arpa/inet.h> //for ntohs() function
#include <stdio.h>
#include <vrouter.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "structure.h"

//***********************************************
// Function: create_neighbor_solicitation() - 
//      build neighbor advertisement packets
//
// Arguments - address - contains our source ethernet address
//      lla - contains our link local ipv6 address to include 
//           as our ipv6 source
//      pNS - the neighbor solicitation packet we are creating
//      packetsize - size of the packet
//***********************************************
void create_neighbor_solicitation(struct ethernet_header &address, struct ip_v6_total_address &lla, 
	struct neighbor_solicitation_advertisement* &pNS, int &packetsize);

//***********************************************
// Function: create_time_exceeded() - 
//      build time exceeded error packets
//
// Arguments - peth - the packet to append at end of packet
//      address - contains our source ethernet address
//      lla - contains our link local ipv6 address to include 
//           as our ipv6 source
//      ptee - the time exceeded error packet we are creating
//      packetsize - size of the packet
//***********************************************
void create_time_exceeded(struct ethr_header* peth,struct ethernet_header &address, struct ip_v6_total_address &lla, 
	struct echo_request_reply* ipv6source, struct time_exceeded_error* &ptee, int &packetsize);

//***********************************************
// Function: create_router_advertisement() - 
//      build router advertisement packets
//
// Arguments - iface - the interface to get the ip prefix for
//      address - contains our source ethernet address
//      lla - contains our link local ipv6 address to include 
//           as our ipv6 source
//      prad - the router advertisement packet we are creating
//      packetsize - size of the packet
//***********************************************
void create_router_advertisement(INTERFACE *iface, struct ethernet_header &address, 
        struct ip_v6_total_address &lla, struct router_advertisement* &prad, int &packetsize);

//***********************************************
// Function: create_neighbor_advertisement() -  
//            build neighbor advertisement packets
//
// Arguments - eh - the structure that holds our interface ethernet address. It is the 
//		source address of the neighbor advertisement packet
//	ga - holds the global ipv6 address to add to the neighbor advertisement packet
//	pns - the neighbor solicitation packet to fill in most of the neighbor advertisement
//		packet. The ethernet source becomes the advertisement's ethernet destination.
//	pna - the neighbor advertisement packet to create
//***********************************************
void create_neighbor_advertisement(struct ethernet_header &eh,struct ip_v6_total_address &ga,struct 
	neighbor_solicitation_advertisement* &pns,struct neighbor_solicitation_advertisement* &pna);

//***********************************************
// Function: create_echo_reply() - 
//            build echo reply packets
//
// Arguments - address - contains our source ethernet address
//	ga - holds the global ipv6 address to add to the echo reply packet
//	request - the echo request packet to fill in most of the echo request
//		packet. The ethernet source becomes the reply's ethernet destination.
//	reply - the echo reply packet to create
//      packetsize - size of the packet
//***********************************************
void create_echo_reply(struct ethernet_header &address, struct ip_v6_total_address &ga, 
	struct echo_request_reply* &request, struct echo_request_reply* &reply, int &packetSize);

//***********************************************
// Function: create_udp_echo_reply() - 
//            build echo reply packets
//
// Arguments - address - contains our source ethernet address
//	ga - holds the global ipv6 address to add to the echo reply packet
//	pudpREQ - the udp echo request packet to fill in most of the echo request
//		packet. The ethernet source becomes the reply's ethernet destination.
//	pudpREP - the udp echo reply packet to create
//      packetsize - size of the packet
//***********************************************
void create_udp_echo_reply(struct ethernet_header &address, struct ip_v6_total_address &ga, struct 
	udp_echo_request_reply* &pudpREQ, struct udp_echo_request_reply* &pudpREP);

//***********************************************
// Function: create_RIPng_packet() - 
//            build RIPng packets
//
// Arguments - rt - pointer to the routing table used to fill the routing
//           table entries in the packet
//      address - contains our source ethernet address
//	ga - holds the global ipv6 address to add to the echo reply packet
//	pRIP - the RIPng packet to create
//      packetsize - size of the packet
//***********************************************
void create_RIPng_packet(struct routing_table* rt,struct ethernet_header &address,struct ip_v6_total_address &ga, 
	struct RIPng_packet* pRIP, int &packetsize);
#endif
