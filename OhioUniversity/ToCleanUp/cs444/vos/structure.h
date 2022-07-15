//************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
//
// Class: CS444
// Project: vos
// File: structures.h
//
// Description: This is the header file for the
//   project wide structures that organize packets
//   for their various and specific data fields.
//************************************************
#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <inttypes.h>

//holds an entry in a routing table
struct routing_table_entry{
  unsigned char address[16];
  unsigned char subnet_mask;
  unsigned char cost;
  unsigned char gateway[16];
  //time_t time_on_table;
  routing_table_entry* next;
};

//holds the routing table
struct routing_table{
  int count;
  struct routing_table_entry* rte;
};

//holds an entry in an arp cache
struct arp_cache_entry{
  unsigned char address[6];
  time_t time_on_table;
};

//holds the arp cache
struct arp_cache{
  int count;
  struct arp_cache_entry* next;
};

//structure that helps hold ipv6 address types
struct ip_v6_total_address{ //16 octets large
  unsigned char total_address[16];
};

//holds the ipv6 base header structure of a packet
struct ip_v6_base_header{ //40 octets large
  unsigned char vers_traffic_class_flow_label[4]; 
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

//holds router advertisement message structure
struct router_advertisement{ //102 octets
  struct ethernet_header eh; //14
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

//holds the icmp echo portion of a packet
struct icmp_echo{
  unsigned char type;
  unsigned char code;
  unsigned short checksum;
  unsigned short identifier;
  unsigned short sequence_number;
};

//holds the structure of an echo request or echo reply packet
struct echo_request_reply{
  struct ethernet_header eh;
  struct ip_v6_base_header v6h;
  struct icmp_echo echo;
  //data...	
};

//holds the pseudo header for checksum calculations
struct pseudo_header{
  struct ip_v6_total_address source;
  struct ip_v6_total_address dest;
  uint32_t icmpv6_length;
  unsigned char zeroes[3];
  unsigned char next_header;
};

//holds the time exceeded portion of a packet
struct time_exceeded_message{
  unsigned char type;
  unsigned char code;
  unsigned short checksum;
  unsigned char unused[4];
  void* packet;
  //1280 bytes mtu
};

//holds the time exceeded error message structure
struct time_exceeded_error{
  struct ethernet_header eh;
  struct ip_v6_base_header v6h;
  struct time_exceeded_message te;
};

//holds the udp header structure
struct udp_header{
  unsigned short source_port;
  unsigned short destination_port;
  unsigned short length;
  unsigned short checksum;
  //data...
};

//holds the structure for udp echos and replies
struct udp_echo_request_reply{
  struct ethernet_header eh;
  struct ip_v6_base_header v6h;
  struct udp_header uh;
  //data...
};

//holds the RIPng header structure
struct RIPng_header{
  unsigned char command;
  unsigned char version;
  unsigned short zero;
  //Route Table Entries 1-N...
};

//holds an RIPng entry
struct RIPng_entry{
  struct ip_v6_total_address ipv6_prefix;
  unsigned short route_tag;
  unsigned char prefix_len;
  unsigned char metric;
};

//holds the RIPng packet structure
struct RIPng_packet{
  struct ethernet_header eh;
  struct ip_v6_base_header v6h;
  struct udp_header uh;
  struct RIPng_header riph;
  //struct RIPng_entry first; //only hold one for the purpose of giving us the ability to send RIPng packets without a working routing table (should be different)
  //entries...  
};
#endif
