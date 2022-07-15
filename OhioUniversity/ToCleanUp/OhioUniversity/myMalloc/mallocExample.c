//"ibm - inside memory management" example code NOT MINE
#include <sys/types.h> //for size_t
#include <stdio.h>

struct memblock{
	size_t memsize;
	int is_available;
	//struct memblock* nextblock;
};
void *managed_memory_start;
void *last_valid_address;
static int initialized=0; //0 if not initialized yet, 1 if initialized

/*return multiples of 8*/
static size_t size_8(size_t size){
	size_t temp=size%8;
	if(temp!=0){
		temp=8-temp;
		size=size+temp;
	}
	return size;
}

void* malloc1(size_t size){
	//ensure our size is a word length minimum KEEP
	size=size_8(size);

	//Holds where we are looking in memory KEEP
	void *current_location;

	//same as current_location, but cast to a memblock KEEP
	struct memblock *current_location_mb;

	//memory location we will return. Will be set to 0 until we find something suitable KEEP
	void *memory_location;

	//Initialize if we haven't already done so
	if(initialized==0){
		last_valid_address=sbrk(0);
		//we don't have any memory to manage yet, so just set the beginning to be last_valid_address
		managed_memory_start=last_valid_address;
		initialized=1;
	}

	//Memory we search for has to include the memblock for book keeping
	size=size+sizeof(struct memblock);
	//Set memory_location to 0 until we find a suitable location
	memory_location = 0;
	//Begin searching at the start of managed memory
	current_location=managed_memory_start;
	//search the free block of memory first
	while(current_location!=last_valid_address){
		//current_location and current_location_mb point to same address.
		//Use current_location to calculate addresses and current_location_mb as our struct
		current_location_mb = (struct memblock *)current_location;
		if(current_location_mb->is_available){
			if(current_location_mb->memsize>=size){
				//We've found an open appropriately-sized location
				//make it no longer available
				current_location_mb->is_available=0;
				//we own it
				memory_location = current_location;
				//leave the loop
				break;
			}
		}
		//If here then current memory block is unsuitable we need to move to the next one
		current_location=current_location+current_location_mb->size;
	}
	//If here then we don't have any memory available. We need to ask the OS for more heap.
	if(memory_location==0){
		//move the end of the heap further back
		sbrk(size);
		//The new memory will be where the last valid address left off
		memory_location=last_valid_address;
		//Now update the last_valid_address from the call to sbrk
		last_valid_address=last_valid_address+size;
		//we need to initialize the memblock
		current_location_mb=memory_location;
		current_lcoation_mb->is_available=0;
		current_location_mb->memsize=size;
	}
	//Now memory_location has the address of the memory, including the memblock
	//move the pointer past the memblock
	memory_location=memory_location+sizeof(struct memblock);
	//return the pointer
	return memory_location;
}
  


int main(){
	int* i=malloc(4);
}
