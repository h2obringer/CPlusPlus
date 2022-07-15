//***************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
//
// Class: CS444
// Project: vos
// File: create.cc
//
// Description: This is the implementation of the create.h
//   functions. Descriptions of functions are in the header file.
//   
//***************************************************
#include "create.h"

void create_neighbor_solicitation(struct ethernet_header &address, 
        struct ip_v6_total_address &lla, struct neighbor_solicitation_advertisement* &pNS, int &packetsize){
  int i=0;
  for(i=0;i<6;++i){ //multicast ethernet destination
    pNS->dest[i]=255;
  }
  for(i=0;i<6;++i){ //our ethernet source
    pNS->source[i]=address.source[i]; 
  }
  pNS->etype=htons(34525); //0x86dd (ipv6)
  pNS->vers_traffic_class_flow_label[0]=32; //version field is only 4 bits long. 
		//32 accounts for offset making version field = 6 (ipv6 specifier)

  for(i=1;i<4;++i){ 
    pNS->vers_traffic_class_flow_label[i]=0;
  }
  pNS->payload_length=32; 
  pNS->next_header=58; //(0x3a) (ICMPv6)
  pNS->hop_limit=255; 
  /*CREATE THE IPV6 MULTICAST DESTINATION ADDRESS FF02::1*/
  pNS->v6_dest[0]=255; //FF
  pNS->v6_dest[1]=2;   //02
  for(i=2;i<15;++i){                      //::
    pNS->v6_dest[i]=0;
  }
  pNS->v6_dest[15]=1;  //01
  /*******************************************************/
  for(i=0;i<16;++i){//source ipv6 address (use our link-local address)
    pNS->v6_source[i]=lla.total_address[i]; 
  }
  pNS->icmpv6_type=135; //type is a neighbor solicitation 
  pNS->icmpv6_code=0;
  pNS->checksum=0;
  for(i=0;i<4;++i){
    pNS->r_s_o_reserved[i]=0;
  }
  for(i=0;i<16;++i){
    pNS->target_address[i]=pNS->v6_dest[i];
  }
  pNS->option_type=1; //source link local address type
  pNS->option_length=8;
  pNS->link_layer_addr[0]=lla.total_address[8];
  pNS->link_layer_addr[1]=lla.total_address[9];
  pNS->link_layer_addr[2]=lla.total_address[10];
  pNS->link_layer_addr[3]=lla.total_address[13];
  pNS->link_layer_addr[4]=lla.total_address[14];
  pNS->link_layer_addr[5]=lla.total_address[15];
  packetsize=86;
}





void create_time_exceeded(struct ethr_header* peth,struct ethernet_header &address, struct ip_v6_total_address &lla, 
	struct echo_request_reply* ipv6source, struct time_exceeded_error* &ptee, int &packetsize){
  int i=0;
  for(i=0;i<6;++i){ //multicasst ethernet destination
    ptee->eh.dest[i]=255;
  }
  for(i=0;i<6;++i){ //our ethernet source
    ptee->eh.source[i]=address.source[i]; 
  }
  ptee->eh.etype=htons(34525); //0x86dd (ipv6)
  ptee->v6h.vers_traffic_class_flow_label[0]=32; //version field is only 4 bits long. 32 accounts for offset making version field = 6 (ipv6 specifier)
  for(i=1;i<4;++i){ 
    ptee->v6h.vers_traffic_class_flow_label[i]=0;
  }
  ptee->v6h.payload_length=sizeof(struct time_exceeded_message)+packetsize;  
  ptee->v6h.next_header=58; //(0x3a) (ICMPv6)
  ptee->v6h.hop_limit=255; 
  
  for(i=0;i<16;++i){
    ptee->v6h.v6_dest.total_address[i]=ipv6source->v6h.v6_source.total_address[i];
  }
  for(i=0;i<16;++i){//source ipv6 address (use our link-local address)
    ptee->v6h.v6_source.total_address[i]=lla.total_address[i]; //our source is the global address
  }
  ptee->te.type=3;
  ptee->te.code=0;
  ptee->te.checksum=0;
  ptee->te.packet=(void*)peth;
  packetsize=packetsize+sizeof(struct time_exceeded_error);
  if(packetsize>1280){ //minimum transission unit is 1280
    packetsize=1280;
  }
}

void create_router_advertisement(INTERFACE *iface, struct ethernet_header &address, 
	struct ip_v6_total_address &lla, struct router_advertisement* &prad, int &packetsize){
  int i=0;
  struct ip_v6_total_address *pfix=(ip_v6_total_address*)malloc(2048); //so compiler doesn't complain...
  void* prefix_buffer=malloc(2048);
  unsigned int *prefix_l=(unsigned int*)malloc(32); //initialize so compiler doesn't complain...
  for(i=0;i<6;++i){
    prad->eh.dest[i]=255;
  }
  for(i=0;i<6;++i){
    prad->eh.source[i]=address.source[i]; 
  }
  prad->eh.etype=htons(34525); //0x86dd (ipv6)
  prad->v6h.vers_traffic_class_flow_label[0]=32; //version field is only 4 bits long. 32 accounts for offset making version field = 6 (ipv6 specifier)
  for(i=1;i<4;++i){ 
    prad->v6h.vers_traffic_class_flow_label[i]=0;
  }
  prad->v6h.payload_length=ntohs(48); //we are assuming it is 48 because vrad packets field was 48
  prad->v6h.next_header=58; //(0x3a) (ICMPv6)
  prad->v6h.hop_limit=1; //we are sending a message meant only for individuals on our network
  /*CREATE THE IPV6 MULTICAST DESTINATION ADDRESS FF02::1*/
  prad->v6h.v6_dest.total_address[0]=255; //FF
  prad->v6h.v6_dest.total_address[1]=2;   //02
  for(i=2;i<15;++i){                      //::
    prad->v6h.v6_dest.total_address[i]=0;
  }
  prad->v6h.v6_dest.total_address[15]=1;  //01
  /*******************************************************/
  for(i=0;i<16;++i){//source ipv6 address (use our link-local address)
    prad->v6h.v6_source.total_address[i]=lla.total_address[i]; //our source is the global address
  }
  prad->ra.type=134; //ICMPv6 type is 134 (router advertisement)
  prad->ra.code=0;
  prad->ra.checksum=0;
  prad->ra.hop_limit=16;
  prad->ra.m_o_reserved=0;
  prad->ra.router_lifetime=0;
  prad->ra.reachable_time[0]=127; //3892510720 milliseconds (value from vrad packets)
  prad->ra.reachable_time[1]=255;
  prad->ra.reachable_time[2]=255;
  prad->ra.reachable_time[3]=255;
  prad->ra.retransmit_timer[0]=127; //3892510720 milliseconds (value from vrad packets)
  prad->ra.retransmit_timer[1]=255;
  prad->ra.retransmit_timer[2]=255;
  prad->ra.retransmit_timer[3]=255;
  if(readipprefixfor(iface, prefix_buffer, prefix_l)==0){
    printf("Failed to retrieved prefix\n");
  }
  pfix=(ip_v6_total_address*)prefix_buffer;
  prad->po.type=3; //prefix option type
  prad->po.length=4;
  prad->po.prefix_length=64; //(unsigned char*)prefix_l;
  prad->po.l_a_reserved1=0;
  prad->po.valid_lifetime[0]=255;
  prad->po.valid_lifetime[1]=255;
  prad->po.valid_lifetime[2]=255;
  prad->po.valid_lifetime[3]=255;
  prad->po.preferred_lifetime[0]=255;
  prad->po.preferred_lifetime[1]=255;
  prad->po.preferred_lifetime[2]=255;
  prad->po.preferred_lifetime[3]=255;
  prad->po.reserved2[0]=255;
  prad->po.reserved2[1]=255;
  prad->po.reserved2[2]=255;
  prad->po.reserved2[3]=255;
  for(i=0;i<16;++i){
    prad->po.prefix[i]=pfix->total_address[i];
  }
  /*NOW DO CHECKSUM CALCULATION*/
  struct pseudo_header* ph=(pseudo_header*)malloc(2048);
  for(i=0;i<16;++i){
    ph->source.total_address[i]=prad->v6h.v6_source.total_address[i];
    ph->dest.total_address[i]=prad->v6h.v6_dest.total_address[i];
  }
  unsigned int packet_length = sizeof(struct ip_v6_router_advertisement) + sizeof(struct prefix_info_option);; 
  ph->icmpv6_length = ntohl(packet_length);
  ph->zeroes[0]=0;
  ph->zeroes[1]=0;
  ph->zeroes[2]=0;
  ph->next_header=58;

  void* position=malloc(2048);
  position=(void*)ph;
  unsigned short pseudo_checksum=htons(vchksum(position,sizeof(struct pseudo_header)));
  position=(void*)&prad->ra;
  unsigned short packet_checksum=htons(vchksum(position,packet_length));
  unsigned short theCheckSum=ntohs(pseudo_checksum)+ntohs(packet_checksum);
  prad->ra.checksum=htons(theCheckSum);
  packetsize=102;
}


void create_echo_reply(struct ethernet_header &address, struct ip_v6_total_address &ga, 
	struct echo_request_reply* &request, struct echo_request_reply* &reply,int &packetSize){
  int i=0;
  reply=request;

  for(i=0;i<6;++i){ //reply's dest is request's source //shouldn't be needed here
    reply->eh.dest[i]=request->eh.source[i];
  }
  for(i=0;i<6;++i){
    reply->eh.source[i]=address.source[i]; 
  }
  for(i=0;i<16;++i){
    reply->v6h.v6_dest.total_address[i]=request->v6h.v6_source.total_address[i];
  }
  for(i=0;i<16;++i){//source ipv6 address (use our link-local address)
    reply->v6h.v6_source.total_address[i]=ga.total_address[i]; //our source is the global address
  }

  //HOPLIMITS

  reply->echo.type+=1; //The icmpv6 type is 129 (1 higher than the echo request type)
  //reply->v6h.payload_length=packetSize-(sizeof(ethernet_header)+sizeof(ip_v6_base_header)); //not correct
  //printf("payload for echo reply= %d\n",reply->v6h.payload_length);
}


void create_neighbor_advertisement(struct ethernet_header &eh, struct ip_v6_total_address &ga, struct 
	neighbor_solicitation_advertisement* &pns, struct neighbor_solicitation_advertisement* &pna){
  int i;
  pna=pns; //most of the data is the same between these packets

  /*the advertisement destination is the solicitation source
  and the advertisement source is the interface ethernet address*/
  for(i=0;i<6;++i){
    pna->dest[i]=pns->source[i];
    pna->source[i]=eh.source[i]; 
  }

  /*the advertisement v6 source is our global address and the 
  advertisement v6 destination is the solicitation v6 source*/
  for(i=0;i<16;++i){
    pna->v6_dest[i]=pns->v6_source[i];    
  }
  for(i=0;i<16;++i){
    pna->v6_source[i]=ga.total_address[i]; //our source is the global address
  } 
  pna->icmpv6_type+=1; //The icmpv6 type is 135
}


void create_udp_echo_reply(struct ethernet_header &address, struct ip_v6_total_address &ga, struct 
	udp_echo_request_reply* &pudpREQ, struct udp_echo_request_reply* &pudpREP){

/*all that is essentially required is switching the ethernet addresses, ipv6 addresses, and port numbers.*/
  int i;
  pudpREP=pudpREQ;

  //the reply destination is the request source
  //and the reply source is the interface ethernet address
  for(i=0;i<6;++i){
    pudpREP->eh.dest[i]=pudpREQ->eh.source[i];
    pudpREP->eh.source[i]=address.source[i]; 
  }
  
  for(i=0;i<16;++i){
    pudpREP->v6h.v6_dest.total_address[i]=pudpREQ->v6h.v6_source.total_address[i];    
  }
  for(i=0;i<16;++i){
    pudpREP->v6h.v6_source.total_address[i]=ga.total_address[i]; //our source is the global address
  }

  pudpREP->uh.source_port=htons(7); //echo port
  pudpREP->uh.destination_port=ntohs(pudpREQ->uh.source_port); //send to sender's port
}


void create_RIPng_packet(struct routing_table* rt,struct ethernet_header &address,struct ip_v6_total_address &ga, 
	struct RIPng_packet* pRIP, int &packetsize){
  int i;
  int j;

  void* temp=(void*)pRIP;
  //the reply destination is the request source
  //and the reply source is the interface ethernet address
  for(i=0;i<6;++i){
    pRIP->eh.dest[i]=255; //multicast destination address
    pRIP->eh.source[i]=address.source[i]; 
  }
  
  /*CREATE THE IPV6 MULTICAST DESTINATION ADDRESS FF02::1*/
  pRIP->v6h.v6_dest.total_address[0]=255; //FF
  pRIP->v6h.v6_dest.total_address[1]=2;   //02
  for(i=2;i<15;++i){                      //::
    pRIP->v6h.v6_dest.total_address[i]=0;
  }
  pRIP->v6h.v6_dest.total_address[15]=1;  //01
  /*******************************************************/
  for(i=0;i<16;++i){
    pRIP->v6h.v6_source.total_address[i]=ga.total_address[i]; //our source is the global address
  }
  pRIP->v6h.next_header=17; //udp type
  pRIP->uh.source_port=htons(521); //coming from our RIPng port
  pRIP->uh.destination_port=htons(521); //send it to the RIPng port
  pRIP->uh.length=sizeof(struct RIPng_header)+((rt->count)*sizeof(RIPng_entry)); //should be correct. rt->count holds the amount of entries in the table.
  pRIP->uh.checksum=0; //we can skip the checksum for udp packets... too much work anyways
  
  pRIP->riph.command=2; //response
  pRIP->riph.version=1;
  pRIP->riph.zero=0;

  temp=temp+sizeof(struct RIPng_packet);//set pointer to router table entry space of packet
  struct RIPng_entry* entry=(struct RIPng_entry*)temp; //structure that space to put data there

  struct routing_table_entry* table_start=rt->rte; //hold the start of our list
  
  for(i=0;i<rt->count;++i){
    for(j=0;j<16;++j){
      entry->ipv6_prefix.total_address[j]=rt->rte->address[j];
    }
    entry->route_tag=0;
    entry->prefix_len=rt->rte->subnet_mask;
    entry->metric=rt->rte->cost;
    rt->rte=rt->rte->next; //go to the next entry in our table
    temp=temp+sizeof(struct RIPng_entry); //set pointer to next available space for a router table entry
    entry=(struct RIPng_entry*)temp; //structure it and now we are ready for the next iteration 
  }
  rt->rte=table_start;
}
