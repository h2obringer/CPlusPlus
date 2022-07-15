//***************************************************
// Author: Randal Mark Obringer
// Email: ro120908@ohio.edu
//
// Class: CS444
// Project: vos
// File: my_utilities.cc
//
// Description: This is the implementation of the my_utilities.h
//   functions. Descriptions of functions are in the header file.
//   Inline comments are provided however to relay my logic.
//   
//***************************************************
#include "my_utilities.h"

void make_link_local_address(struct ip_v6_total_address &link_local_address, lanlist* myLanList){
	int j=0;
	int k=0;
	unsigned char modifier=2; //used to perform bitwise operations for the link local address 
		//and the global address

	//create the linklocal prefix portion (FE80:0000:0000:0000)
	link_local_address.total_address[0]=254; //FE
	link_local_address.total_address[1]=128; //80
	link_local_address.total_address[2]=0; //00
	link_local_address.total_address[3]=0; //00
	link_local_address.total_address[4]=0; //00
	link_local_address.total_address[5]=0; //00
	link_local_address.total_address[6]=0; //00
	link_local_address.total_address[7]=0; //00

	//fill in the ethernet address portion by splitting the ethernet address in half and adding FFFE in the middle
	k=8; //keeps track of where we are in filling in our link local address
	j=0; //keeps track of where we are on our ethernet address for when we are breaking it appart
	while(k<16){
		if(k==11){//add FFFE in the appropriate spots
			link_local_address.total_address[k]=255; //FF
		}else if(k==12){
			link_local_address.total_address[k]=254; //FE
		}else{
			link_local_address.total_address[k]=merge(myLanList->lan->hwaddr[j],myLanList->lan->hwaddr[j+1]);
			if(k==8){ //if its the first octet in the second half of the address
				//flip the second to lowest order bit
				if((link_local_address.total_address[k]&modifier)==2){ 
					link_local_address.total_address[k]-=2;
				}else{
					link_local_address.total_address[k]+=2;
				}
			}
			j=j+3; //increase to the next unused portion of the address from hwaddr in myLanList
		}
		++k; //move on to the next portion of our link-local address to fill in
	}
}

void make_simple_address(char* tempBuff, struct ip_v6_total_address &address, std::string &container){
	sprintf(tempBuff,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",address.
		total_address[0],address.total_address[1],address.total_address[2],address.total_address[3],
		address.total_address[4],address.total_address[5],address.total_address[6],address.
		total_address[7],address.total_address[8],address.total_address[9],address.total_address[10],
		address.total_address[11],address.total_address[12],address.total_address[13],address.
		total_address[14],address.total_address[15]);
	container=tempBuff;  
} 

void condense_ethernet_address(lanlist* myLanList, struct ethernet_header &address_holder){
	address_holder.source[0]=merge(myLanList->lan->hwaddr[0],myLanList->lan->hwaddr[1]); 
	address_holder.source[1]=merge(myLanList->lan->hwaddr[3],myLanList->lan->hwaddr[4]);
	address_holder.source[2]=merge(myLanList->lan->hwaddr[6],myLanList->lan->hwaddr[7]);
	address_holder.source[3]=merge(myLanList->lan->hwaddr[9],myLanList->lan->hwaddr[10]);
	address_holder.source[4]=merge(myLanList->lan->hwaddr[12],myLanList->lan->hwaddr[13]);
	address_holder.source[5]=merge(myLanList->lan->hwaddr[15],myLanList->lan->hwaddr[16]);
}

void handle_router_advertisements(char* tempBuff, struct ethr_header* peth, void* packetHolder,
	struct ip_v6_total_address global_address, int &address_determined, std::string &my_global, int i){
	int j=0;
	struct router_advertisement* prad=(router_advertisement*)malloc(2048); //extract 
		//the data of packets sent from the vrad program 
		//with the correct data segments in place

	if(peth->data[40]==134){ //if router advertisement
		prad=(router_advertisement*)packetHolder; //structure it properly
		for(j=0;j<8;++j){ //grab the rest of our local address from the prefix option
			global_address.total_address[j]=prad->po.prefix[j];
		}
		address_determined=1; //set the flag that we have our global address for this interface

		//put the address in a more convenient container
		make_simple_address(tempBuff,global_address, my_global);
		printf("Global Address for eth%d IPv6\n",i+1);
		cout << my_global << endl;
	}
}

void handle_neighbor_solicitations(char* tempBuff,struct ethr_header* peth,void* packetHolder,std::string my_local,
		std::string my_global,struct ip_v6_total_address global_address,struct ethernet_header address_holder,
		int &sizeOfPacket,int &debug,INTERFACE* interfaceHolder){
	struct neighbor_solicitation_advertisement* pNS=(neighbor_solicitation_advertisement*)malloc(2048); 
		//aid in building a proper neighbor advertisement packet)
	struct neighbor_solicitation_advertisement* pNA; //extract the data from neighbor 
		//solicitation packets sent from the vping6 program with the correct 
		//data segments in place
	std::string packetTarget; //place to store the simplified ipv6 address

	/*IF PACKET IS A NEIGHBOR SOLICITATION (type 0x87)*/
	if(peth->data[40]==135){
		pNS=(neighbor_solicitation_advertisement*)packetHolder; //structure it properly

		//store target address in a more convenient container for comparison
		if(sprintf(tempBuff,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
				pNS->target_address[0],pNS->target_address[1],pNS->target_address[2],
				pNS->target_address[3],pNS->target_address[4],pNS->target_address[5],
				pNS->target_address[6],pNS->target_address[7],pNS->target_address[8],
				pNS->target_address[9],pNS->target_address[10],pNS->target_address[11],
				pNS->target_address[12],pNS->target_address[13],pNS->target_address[14],
				pNS->target_address[15])!=0){
			packetTarget=tempBuff; 
		}
				   
		/*IF TARGET ADDRESS IS OUR LINK LOCAL OR GLOBAL ADDRESS*/
		if((packetTarget==my_local)||(packetTarget==my_global)){
			//create a neighbor advertisement packet in response to the neighbor solicitation packet
			create_neighbor_advertisement(address_holder,global_address,pNS,pNA); 
			packetHolder=(void*)pNA;
			if(writepacket(interfaceHolder,packetHolder,sizeOfPacket)==-1){
				printf("Failed to send a neighbor advertisement\n");
			}else{
				if(debug>0){
					printf("Neighbor Advertisement sent in reply to the Neighbor Solicitation\n");
				}
			}
		}//end target address is link local or global address
	}//end neighbor solicitation (type 0x87)*/
}

void handle_echo_requests(char* tempBuff,struct ethr_header* peth,void* packetHolder,std::string my_local,
		std::string my_global,struct ip_v6_total_address global_address,struct ethernet_header address_holder,
		int &sizeOfPacket,int &debug,INTERFACE* interfaceHolder){
	struct echo_request_reply* echo_reply=(echo_request_reply*)malloc(2048); //extract the data 
		//from echo request packets sent

	struct echo_request_reply* echo_request=(echo_request_reply*)malloc(2048);
		//sent from the vping6 program with the correct data segments in place
	std::string packetTarget; //place to store the simplified ipv6 address

	/*IF ETHERNET TYPE IS IPV6 (type 0x86dd)*/
	if(ntohs(peth->etype)==34525){
		echo_request=(echo_request_reply*)packetHolder; //structure it properly
		//store the packet ipv6 destination in a more convenient container for comparison purposes
		if(sprintf(tempBuff,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
				echo_request->v6h.v6_dest.total_address[0],echo_request->v6h.v6_dest.total_address[1],
				echo_request->v6h.v6_dest.total_address[2],echo_request->v6h.v6_dest.total_address[3],
				echo_request->v6h.v6_dest.total_address[4],echo_request->v6h.v6_dest.total_address[5],
				echo_request->v6h.v6_dest.total_address[6],echo_request->v6h.v6_dest.total_address[7],
				echo_request->v6h.v6_dest.total_address[8],echo_request->v6h.v6_dest.total_address[9],
				echo_request->v6h.v6_dest.total_address[10],echo_request->v6h.v6_dest.total_address[11],
				echo_request->v6h.v6_dest.total_address[12],echo_request->v6h.v6_dest.total_address[13],
				echo_request->v6h.v6_dest.total_address[14],echo_request->v6h.v6_dest.total_address[15])!=0){
			packetTarget=tempBuff;
		}
		/*IF IPV6 DESTINATION IS EITHER OUR LINK LOCAL OR GLOBAL ADDRESS*/
		if((my_local==packetTarget)||(my_global==packetTarget)){
			if(debug>0){
				printf("The target address is meant for us\n");
			}
			/*IF PACKET IS AN ECHO REQUEST (type 0x80)*/
			if(peth->data[40]==128){ 
					 
				//create an echo reply packet in response to an echo request packet
				create_echo_reply(address_holder,global_address,echo_request,echo_reply,sizeOfPacket);                
				packetHolder=(void*)echo_reply;
				if(writepacket(interfaceHolder,packetHolder,sizeOfPacket)==-1){
					printf("Failed to send an echo reply\n");
				}else{
					if(debug>0){
						printf("Echo Reply sent in reply to an Echo Request\n");
					}
				}
			}
		}
	}
}

void handle_time_exceeded_errors(struct ethr_header* peth,void* packetHolder,
		struct ip_v6_total_address link_local_address,struct ethernet_header address_holder,
		int &sizeOfPacket,int &debug,int &hopCount,int &hopTest,int &is_router,INTERFACE* interfaceHolder){

	struct echo_request_reply* echo_reply=(echo_request_reply*)malloc(2048); //extract the data 
		//from echo request packets sent

	struct time_exceeded_error* ptee=(time_exceeded_error*)malloc(2048); //our well formed packet to create

	echo_reply=(echo_request_reply*)packetHolder; //use to get the hopcount from it (structure it for the hopcount)
	hopCount=echo_reply->v6h.hop_limit;
	--hopCount; //we will update the hopCount when we create packets or send them off 
	hopTest=0; //reset the test
	if(debug>0){
		printf("HOP COUNT after updating= %d\n",hopCount);
	}
	if(is_router>0){ //if we are a router
		if(hopCount==0){ //DO OUR HOP CHECK
			if((address_holder.source[0]!=peth->dest[0])&&(address_holder.source[1]!=peth->dest[1])
					&&(address_holder.source[2]!=peth->dest[2])&&(address_holder.source[3]!=peth->dest[3])
					&&(address_holder.source[4]!=peth->dest[4])&&(address_holder.source[5]!=peth->dest[5])){
				if((peth->dest[0]!=255)&&(peth->dest[1]!=255)&&(peth->dest[2]!=255)&&(peth->dest[3]!=255)&&
						(peth->dest[4]!=255)&&(peth->dest[5]!=255)){
					hopTest=1; //hop test passed so we will not do anything further in our program with the packet
					create_time_exceeded(peth,address_holder, link_local_address,echo_reply, ptee,sizeOfPacket);
					if(writepacket(interfaceHolder,packetHolder,sizeOfPacket)==-1){
						printf("Failed to send Time Exceeded Error\n");
					}else{
						if(debug>0){
							printf("Time Exceeded Error sent\n");
						}
					}
				}
			}
		}
	}
}

void handle_router_responsibilities(struct routing_table* rt,void* packetHolder,struct ip_v6_total_address link_local_address,
		struct ethernet_header address_holder,int &sizeOfPacket,int &debug,INTERFACE* interfaceHolder){

	struct router_advertisement* prad=(router_advertisement*)malloc(2048); //extract 
		//the data of packets sent from the vrad program 
		//with the correct data segments in place
	struct RIPng_packet* pRIP=(RIPng_packet*)malloc(2048);

	create_router_advertisement(interfaceHolder, address_holder, link_local_address, prad, sizeOfPacket);
	packetHolder=(void*)prad; //structure it
	if(writepacket(interfaceHolder,packetHolder,sizeOfPacket)==-1){
		printf("Failed to send a Router Advertisement\n");
	}else{
		if(debug>0){
			printf("Router Advertisement sent\n");
		}
	}

	create_RIPng_packet(rt,address_holder,link_local_address,pRIP,sizeOfPacket);
	packetHolder=(void*)pRIP; //structure it
	if(writepacket(interfaceHolder,packetHolder,sizeOfPacket)==-1){
		printf("Failed to send a RIPng packet\n");
	}else{
		if(debug>0){
			printf("RIPng packet sent\n");
		}
	}
}

void send_neighbor_discovery_packets(void* packetHolder,struct ip_v6_total_address link_local_address,
		struct ethernet_header address_holder,int &sizeOfPacket,int &debug,INTERFACE* interfaceHolder){

	struct neighbor_solicitation_advertisement* pNS=(neighbor_solicitation_advertisement*)malloc(2048); 
		//aid in building a proper neighbor advertisement packet

	create_neighbor_solicitation(address_holder, link_local_address, pNS, sizeOfPacket);
	packetHolder=(void*)pNS;
	if(writepacket(interfaceHolder,packetHolder,sizeOfPacket)==-1){
		printf("Failed to send a Neighbor Solicitation\n");
	}else{
		if(debug>0){
			printf("Neighbor Solicitation sent\n");
		}
	}
}

void handle_udp_echo(char* tempBuff,struct ethr_header* peth,void* packetHolder,struct 
		ip_v6_total_address global_address,std::string my_local,std::string my_global,
		struct ethernet_header address_holder,int &sizeOfPacket,int &debug,INTERFACE* interfaceHolder){

	struct udp_echo_request_reply* uRequest=(udp_echo_request_reply*)malloc(2048);
	struct udp_echo_request_reply* uReply=(udp_echo_request_reply*)malloc(2048);
	std::string packetTarget;

	if(sprintf(tempBuff,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
		uRequest->v6h.v6_dest.total_address[0],uRequest->v6h.v6_dest.total_address[1],
		uRequest->v6h.v6_dest.total_address[2],uRequest->v6h.v6_dest.total_address[3],
		uRequest->v6h.v6_dest.total_address[4],uRequest->v6h.v6_dest.total_address[5],
		uRequest->v6h.v6_dest.total_address[6],uRequest->v6h.v6_dest.total_address[7],
		uRequest->v6h.v6_dest.total_address[8],uRequest->v6h.v6_dest.total_address[9],
		uRequest->v6h.v6_dest.total_address[10],uRequest->v6h.v6_dest.total_address[11],
		uRequest->v6h.v6_dest.total_address[12],uRequest->v6h.v6_dest.total_address[13],
		uRequest->v6h.v6_dest.total_address[14],uRequest->v6h.v6_dest.total_address[15])!=0){
		packetTarget=tempBuff;
	}

	/*IF IPV6 DESTINATION IS EITHER OUR LINK LOCAL OR GLOBAL ADDRESS*/
	if((my_local==packetTarget)||(my_global==packetTarget)){
		if(peth->data[40]==17){ //udp type
			if(htons(uRequest->uh.destination_port)==7){ //if directed at the echo port
				create_udp_echo_reply(address_holder, global_address, uRequest,uReply);
				packetHolder=(void*)uReply;
				if(writepacket(interfaceHolder,packetHolder,sizeOfPacket)==-1){
					printf("Failed to send a Neighbor Solicitation\n");
				}else{
					if(debug>0){
						printf("UDP echo sent in response to a UDP echo\n");
					}
				}
			}
		}
	}
}

void recieve_RIPng_packets(struct routing_table* rt,struct ethr_header* peth,void* packetHolder,int &sizeOfPacket,int &debug){
	int i=0;
	int space_left=sizeOfPacket; //holds the size of routing table entries left in the packet. when it is 0 we can stop pulling entries out of the packet.
	space_left-=sizeof(RIPng_packet);//get the size of the routing table entries (RIPng_packet contains only up to the header of a rip packet)
	struct RIPng_packet* pRIP=(RIPng_packet*)packetHolder;
	void* pointer=packetHolder;
	struct RIPng_entry* entry; //allow us to structure the entries to put in our table
	struct routing_table_entry* table_start=rt->rte; //hold the start of our list
	while(rt->rte!=NULL){
		rt->rte=rt->rte->next;
	} //walk to the end of the list

	if(peth->data[40]==17){ //udp type
		if(pRIP->uh.destination_port==521){ //if port destination is RIPng port
			pointer=pointer+sizeof(struct RIPng_packet);//move position to beginning entry position
			entry=(RIPng_entry*)pointer; //structure the entry
			while(space_left>0){ //while still table entries present
				rt->count++; //increase # of entries in our table

				rt->rte=new struct routing_table_entry; //allocate space for a new entry in the table
				for(i=0;i<16;++i){
					rt->rte->address[i]=entry->ipv6_prefix.total_address[i]; //obtain the address
					rt->rte->gateway[i]=pRIP->v6h.v6_source.total_address[i]; //obtain the gateway
				}
				rt->rte->subnet_mask=entry->prefix_len;
				rt->rte->cost=entry->metric+1; //the cost is one more for us
				if(table_start==NULL){ //if the head of the list was NULL we don't want it pointing there we want it pointing to the first element of the list
					table_start=rt->rte;
				}
				space_left-=sizeof(struct routing_table_entry); //because we just extracted an entry subtract the size of entries we have left to look at
				rt->rte->next=NULL; //set next to NULL
				rt->rte=rt->rte->next; //then move to that spot so we can make a new entry if there are more routing table entries in the packet.

				pointer=pointer+sizeof(struct RIPng_entry);//move position to beginning of next entry
				entry=(RIPng_entry*)pointer; //structure the entry
				//start pulling data...
			}
			rt->rte=table_start; //when finished adding entries move to the beginning of the list again for later use.
			if(debug>0){
				printRoutingTable(rt);
			}
		}
	}
}
