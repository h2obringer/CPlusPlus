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
//   Note: this does not provide prototypes for the 
//   helper functions used by the printing function
//************************************************

#ifndef PRINT_H
#define PRINT_H

#include <arpa/inet.h> //for ntohs() function
#include <stdio.h>

//structure that helps hold ipv6 address types
struct ip_v6_total_address{ //16 octets large
	unsigned char total_address[16];
};

//holds the ipv6 base header structure of a packet
struct ip_v6_base_header{ //40 octets large
	unsigned char vers_traffic_class_flow_label[3]; 
	unsigned short payload_length; 
	unsigned char next_header; 
	unsigned char hop_limit; 
	struct ip_v6_total_address v6_source; 
	struct ip_v6_total_address v6_dest; 
};

//holds the ipv6 router advertisement packet structure
struct ip_v6_router_advertisement{ //16 octets
	unsigned char type; 
	unsigned char code; 
	unsigned short checksum; 
	unsigned char hop_limit; 
	unsigned char m_o_reserved;
	unsigned short router_lifetime; 
	unsigned char reachable_time[4]; 
	unsigned char retransmit_timer[4]; 
};

//holds the prefix information option structure of a packet
struct prefix_info_option{ //32 octets large
	unsigned char type; 
	unsigned char length;
	unsigned char prefix_length; 
	unsigned char l_a_reserved1; 
	unsigned char valid_lifetime[4]; 
	unsigned char preferred_lifetime[4]; 
	unsigned char reserved2[4];
	unsigned char prefix[16]; 
};

//holds the ethernet structure of a packet
struct ethernet_header{ //14 octets large
	unsigned char dest[6];
	unsigned char source[6]; 
	unsigned short etype; 
};

//holds raw packet data while only recognizing the ethernet portions of a packet.
//Used to analyze packets for debugging or simply quick data gathering
struct ethr_header{
	unsigned char dest[6]; 
	unsigned char source[6]; 
	unsigned short etype; 
	unsigned char data[72];
};

//holds the broken down structures of a vrad program packet
struct vrad_packet{ //102 octets
	struct ethernet_header eh;
	struct ip_v6_base_header v6h;
	struct ip_v6_router_advertisement ra;
	struct prefix_info_option po;
};

//holds the structure of a neighbor solicitation or neighbor advertisement packet
struct neighbor_solicitation_advertisement{
	unsigned char dest[6];
	unsigned char source[6]; 
	unsigned short etype;
	unsigned char vers_traffic_class_flow_label[4];
	unsigned short payload_length; 
	unsigned char next_header; 
	unsigned char hop_limit; 
	unsigned char v6_source[16];
	unsigned char v6_dest[16];
	unsigned char icmpv6_type;
	unsigned char icmpv6_code;
	unsigned short checksum;
	unsigned char r_s_o_reserved[4];
	unsigned char target_address[16];
	unsigned char option_type;
	unsigned char option_length;
	unsigned char link_layer_addr[6];
};

//holds the structure of an echo request or echo reply packet
//modified specifically for the packets sent by vping6
struct echo_request_reply{ //101 octets
	unsigned char dest[6];		
	unsigned char source[6];		
	unsigned short etype;			
	unsigned char vers_traffic_class_flow_label[4];
	unsigned short payload_length;	
	unsigned char next_header;		
	unsigned char hop_limit;		
	unsigned char v6_source[16];		
	unsigned char v6_dest[16];		
	unsigned char icmpv6_type;		
	unsigned char icmpv6_code;		
	unsigned short checksum;		
	unsigned short identifier;		
	unsigned short sequence_number;	
	unsigned char data[39];		
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


//***********************************************
// Function: create_neighbor_advertisement() - create a neighbor advertisement packet.
//	Sends a packet to the source of the solicitation packet. The source of the packet
//      is the interace ethernet address. 
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
// Function: create_echo_reply() - create an echo reply packet.
//	Sends a packet to the source of the echo request packet. The source of the packet
//      is the interace ethernet address. 
//
// Arguments - eh - the structure that holds our interface ethernet address. It is the 
//		source address of the neighbor advertisement packet
//	ga - holds the global ipv6 address to add to the neighbor advertisement packet
//	ereq - the echo request packet to fill in most of the echo request
//		packet. The ethernet source becomes the reply's ethernet destination.
//	erep - the echo reply packet to create
//***********************************************
void create_echo_reply(struct ethernet_header &eh,struct ip_v6_total_address &ga,struct echo_request_reply*
	&ereq,struct echo_request_reply* &erep);

#endif
