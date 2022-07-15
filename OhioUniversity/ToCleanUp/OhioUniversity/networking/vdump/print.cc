//***************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
// Coauthor:Professor Osterman (skeleton of program)
//
// Class: CS444
// Project: vdump
// File: print.cc
//
// Description: This is the implementation of the print
//   packet function
//   
//***************************************************
#include "print.h"
#include "filter.h"

static int packetCount=1; //keep track of the number of packets we have printed

void printpacket(int packetSize,unsigned char *buf, int len,struct ethr_header* peth,
	char* sf, char* df){

	/*Always filter here. We can allow this due to the default filters which provide
	wild-cards*/
	if( filter_matches(sf,peth->source) && filter_matches(df,peth->dest) ){
		peth=(ethr_header*) buf; //structure our data

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
		for(a=0;a<40;++a){
			if(a==19){
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

