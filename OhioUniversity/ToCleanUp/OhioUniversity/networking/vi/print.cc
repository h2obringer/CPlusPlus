//***************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
// Coauthor:Professor Osterman (skeleton of program)
//
// Class: CS444
// Project: vdump
// File: print.cc
//
// Description: This is the implementation of the print.h
//   funcitons. Descriptions of functions are in the header file.
//   
//***************************************************
#include "print.h"
#include "filter.h"

static int packetCount=1; //keep track of the number of packets we have printed


void create_neighbor_advertisement(struct ethernet_header &eh,struct ip_v6_total_address &ga,struct 
	neighbor_solicitation_advertisement* &pns,struct neighbor_solicitation_advertisement* &pna){
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
		pna->v6_source[i]=ga.total_address[i]; //our source is the global address
		pna->v6_dest[i]=pns->v6_source[i];
	}
	pna->icmpv6_type+=1; //The icmpv6 type is 135
}


void create_echo_reply(struct ethernet_header &eh,struct ip_v6_total_address &ga,struct echo_request_reply*
	&ereq,struct echo_request_reply* &erep){
	int i;
	erep=ereq; //most of the data is the same between these packets.
  
	/*the echo reply destination is the request source and the
	reply source is the interface ethernet address*/
	for(i=0;i<6;++i){
		erep->dest[i]=ereq->source[i];
		erep->source[i]=eh.source[i]; 
	}
	/*the echo reply v6 source is our global address and the
	echo reply v6 destination is the request's v6 source*/
	for(i=0;i<16;++i){
		erep->v6_source[i]=ga.total_address[i]; 
		erep->v6_dest[i]=ereq->v6_source[i];
	}
	erep->icmpv6_type+=1; //The icmpv6 type is 129

}

void printpacket(int packetSize,unsigned char *buf, int len,struct ethr_header* peth,
	char* sf, char* df){

	/*Always filter here. We can allow this due to the default filters which provide
	wild-cards*/

	if( filter_matches(sf,peth->source) && filter_matches(df,peth->dest) ){
		peth=(ethr_header*) buf; //structure our data

		if(peth->data[40]==135){
			printf("Neighbor solicitation (vdump)\n");
		}else if(peth->data[40]==136){
			printf("Neighbor advertisement (vdump)\n");
		}else if(peth->data[40]==134){
			printf("Router advertisement (vdump)\n");
		}else if(peth->data[40]==128){
			printf("Echo request (vdump)\n");
		}else if(peth->data[40]==129){
			printf("Echo reply (vdump)\n");
		}

		//print the size of the packet and our packet count
		printf("packet %d - length %d bytes:\n",packetCount,packetSize);

		//print the packet hardware destination
		int a=(int)peth->dest[0];
		int b=(int)peth->dest[1];
		int c=(int)peth->dest[2];
		int d=(int)peth->dest[3];
		int e=(int)peth->dest[4];
		int f=(int)peth->dest[5];
		printf("  Eth Dest: %02x:%02x:%02x:%02x:%02x:%02x\n",a,b,c,d,e,f);

		//print the packet hardware soure
		a=(int)peth->source[0];
		b=(int)peth->source[1];
		c=(int)peth->source[2];
		d=(int)peth->source[3];
		e=(int)peth->source[4];
		f=(int)peth->source[5];
		printf("  Eth Src: %02x:%02x:%02x:%02x:%02x:%02x\n",a,b,c,d,e,f);

		//print the packet ethernet type
		printf("  Eth Type: %#hx\n",ntohs(peth->etype));

		//finally print the packet's first 40 bytes of data
		printf("  Eth Data:\n      "); 
		for(a=0;a<72;++a){
			if((a==19)||(a==39)||(a==59)){
				printf("%02x\n      ",peth->data[a]);
			}else{
				printf("%02x ",peth->data[a]);
			}
		}
		printf("\n\n");

		++packetCount; //keep track of how many packets we've printed
	}
	return;
}

