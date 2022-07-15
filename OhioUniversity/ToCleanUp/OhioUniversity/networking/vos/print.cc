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

void printRoutingTable(struct routing_table* rt){
	struct routing_table_entry* table_start=rt->rte; //hold the start of our list
	printf("Entry/SubnetMask                         Gateway                               Cost\n");
	printf("---------------------------------------  ------------------------------------  ----\n");
	while(rt->rte!=NULL){
		printf("%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x/%d",rt->rte->address[0],
		rt->rte->address[1],rt->rte->address[2],rt->rte->address[3],rt->rte->address[4],rt->rte->address[5],
		rt->rte->address[6],rt->rte->address[7],rt->rte->address[8],rt->rte->address[9],rt->rte->address[10],
		rt->rte->address[11],rt->rte->address[12],rt->rte->address[13],rt->rte->address[14],rt->rte->address[15],
		rt->rte->subnet_mask);
		printf("%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x  ",rt->rte->gateway[0],
		rt->rte->gateway[1],rt->rte->gateway[2],rt->rte->gateway[3],rt->rte->gateway[4],rt->rte->gateway[5],
		rt->rte->gateway[6],rt->rte->gateway[7],rt->rte->gateway[8],rt->rte->gateway[9],rt->rte->gateway[10],
		rt->rte->gateway[11],rt->rte->gateway[12],rt->rte->gateway[13],rt->rte->gateway[14],rt->rte->gateway[15]);
		printf("%d\n",rt->rte->cost);
		rt->rte=rt->rte->next; //go to the next entry
	}
	rt->rte=table_start; //restore the head of the list
}

void printVosHelp(){
	printf("Vos help:\n\n");
	printf("Arguments for Vos should be given in the following form:\n");
	printf("./vos [-d] [-l] [-g NUM] [-D] [-a SECONDS] [-h]\n\n");
	printf("    -d: print debugging information during execution of program\n");
	printf("    -l: print a list of interfaces with the name and hardware addresses\n");
	printf("    -g NUM: set the group number to NUM for use over the internet\n");
	printf("    -D: connect this machine to the DSL interface for communicaiton with the actual internet\n");
	printf("    -a SECONDS: specify the number of seconds that an entry in the ARP table is allowed to exist\n");
	printf("    -h: print the help screen and the arguments given to the command line\n\n");
	printf("Arguments given were:\n");
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

