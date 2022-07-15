//************************************************************
// 	"A Re-Implementation of the Malloc Function"
// Authors: Randal Mark Obringer and Leni Austin 
// School: Ohio University
// Email: ro120908@ohio.edu
//
//
// Class: CS442 (Operating Systems)
// Professor: Frank Drews
//
// File: mymalloc.c
// Description: This is my implementation of the malloc, calloc,
//   realloc, and free dynamic memory functions. These functions 
//   work with a linked list data structure to keep track of free
//   memory blocks and memory is given at a first fit basis.
//   The beginning of the free list can be found by a reference to the
//   global pointer begin_freelist. The beginning and the end of the heap
//   which is altered, is stored by the global pointers managed_memory_start
//   and last_valid_address respectively.
//   These functions exact descriptions, in detail, are given above the
//   implementation of each funciton.
// Input: Most input is the size of the space you want. Each of these
//   functions has their own parameters however.
// Bugs: These functions when working together have a noticeable amount
//   of bugs. Malloc seems to work in allocating space. Certain amounts of calls to malloc
//   seem to break this function however and with different sizes. Calling only a single free
//   can be executed and it works. Any later calls to free causes the program to segfault.
//   Whether this is due to a bookkeeping error inside the malloc function
//   or because of a bookkeeping error in free is unsure and has not been pin
//   pointed. Because calloc and realloc call malloc and malloc is the suspected
//   culprit of the problems, we suspect calloc and realloc to be working properly
//   as all they do is make another system call after calling malloc. 
//
// Last Updated: 3 March 2012
//
//************************************************************

#include "mymalloc.h"
/*our structure for book keeping*/
struct memblock{ 
	size_t memsize;
	struct memblock* nextblock;
};

/************************GLOBAL VARIABLES***************************/
static void *managed_memory_start; //holds the start of the heap
static void *last_valid_address; //holds the end of the allocated heap
static int initialized=0; //tells if the heap has been initialized or not
static struct memblock* begin_freelist; //holds the beginning of the free memblocks
/*******************************************************************/

/***************************DEFINITIONS*****************************/
#define WORDSIZE 8    //minimum dynamic memory size allowed
#define FOUR_K 4096   //size of 4k, normally the size of a page in memory.
#define EIGHT_K 8192  //size of 8k, occassionally the size of a page in memory.
#define _FALSE 0      //tell if a statement is false
#define _TRUE 1       //tell if a statement is true
#define NOTHING 0     //things that need to be 0
#define START 0       //used with sbrk to give the start of the heap
/*******************************************************************/

/************************PROTOTYPES*********************************/
static size_t size_8(size_t size);
static size_t size_to_increase_heap(size_t size);
/*******************************************************************/


/****************************************************** 
  size_8 - Ensures that the argument (size) is divisible
     by 8. Returns the new size.

  Arguments: size - the size to make divisible by 8 
     if not already
*******************************************************/
static size_t size_8(size_t size){
	size_t temp=size%WORDSIZE;
	if(temp!=NOTHING){
		temp=WORDSIZE-temp;
		size=size+temp;
	}
	return size;
}

/****************************************************** 
  size_to_increase_heap - Ensures that the heap is always 
     increased by atleast 8k. Also ensures that enough
     space is allocated for larger variables.

  Arguments: size - the size needed to decide what our
     expansion size of the heap will be
*******************************************************/
static size_t size_to_increase_heap(size_t size){
	size_t temp_size;
	if(size<EIGHT_K){ //if need less than 8k then allocate 8k
		return EIGHT_K;
	}else{ //ensure that we are allocating big enough for the size requested and big enough for a page size
		temp_size=size/FOUR_K;
		temp_size=temp_size*EIGHT_K;
		return temp_size;
	}
}

/****************************************************** 
  malloc1 - Allocates memory and keeps track of free 
     memory blocks by means of a linked list. Uses a first
     fit method when searching for memory blocks. Will resize
     memory blocks that are bigger than what is needed. 
     Uses the list of free memory to always return our memory.
     If no free memory is found it expands the heap then maintains
     the free list and then resizes whichever block needs it.
  Arguments: size - the size the space needs to be to 
     hold the dynamic data
*******************************************************/

void* malloc(size_t size){
	if(size==NOTHING){
		return (void*)NULL;
	}
	size_t temp;
	size=size_8(size);
	void *current_location;
	struct memblock *current_location_mb;
	void *memory_location=NULL;
	struct memblock *new_mb;
	struct memblock *prev_location_mb;

	/*If first time calling malloc, there is nothing on the heap so create it*/
	if(initialized==_FALSE){
		managed_memory_start=(void*)sbrk(START);
		last_valid_address=(void*)sbrk(EIGHT_K); //8K
		current_location_mb=(struct memblock*)managed_memory_start;
		current_location_mb->memsize=(last_valid_address-managed_memory_start)-sizeof(struct memblock);
		current_location_mb->nextblock=NULL;
		begin_freelist=current_location_mb;
		initialized=_TRUE;
	}

	current_location_mb=begin_freelist;
	prev_location_mb=current_location_mb;

	/*Search the free memblocks for a spot*/
	while(current_location_mb!=NULL){
		/*If a memblock is big enough to fill the request*/
		if(current_location_mb->memsize >= size){
			//write(STDOUT_FILENO,"Big enough\n",11); //DEBUGGING
			current_location = (void*)current_location_mb;
			/*Move to the beginning of the data segment*/
			current_location=current_location+sizeof(struct memblock); 
			/*We will return memory_location after we do some book keeping*/
			memory_location=current_location; 
			/*Move to the end of the data segment incase we can split the memblock into more blocks*/
			current_location=current_location+size; 
			/*after filling this memblock, can it support holding another memblock???*/
			temp = current_location_mb->memsize - (size+sizeof(struct memblock)+WORDSIZE);
			/*if it cannot support another memblock then...*/
			if(temp<NOTHING){ 
				/*Give the entire block to the data being requested 
				and maintain integrity of the free list of memblocks*/
				if(begin_freelist==current_location_mb){
					begin_freelist=current_location_mb->nextblock;
					current_location_mb->nextblock=NULL;
				}else{
					prev_location_mb->nextblock=current_location_mb->nextblock;
					current_location_mb->nextblock=NULL;
				}
				/*Finally return the data and exit*/
				return memory_location;
			/*if it can support another memblock then...*/
			}else{
				/*create and initialize the new memblock*/
				new_mb=(struct memblock*)current_location;
				new_mb->memsize=current_location_mb->memsize-(size+sizeof(struct memblock));
				new_mb->nextblock=NULL;
				/*resize the first memblock*/
				current_location_mb->memsize=size;
				/*Maintain the integrity of the free list of memblocks*/
				if(current_location_mb==begin_freelist){
					begin_freelist=new_mb;
					new_mb->nextblock=current_location_mb->nextblock;
					current_location_mb->nextblock=NULL;
				}else{
					prev_location_mb->nextblock=new_mb;
					current_location_mb->nextblock=NULL;
				}
				/*Finally return the data and exit*/
				return memory_location;
			}
		/*If memblock is not big enough move to the next one,
		maintain the previous memblock to allow book keeping to 
		work later on*/
		}else{ 
			current_location_mb=current_location_mb->nextblock;
			if(prev_location_mb->nextblock!=current_location_mb){
				prev_location_mb=prev_location_mb->nextblock;
			}
		}
	}//end while loop

	/*If here then there is either nothing on the free list of memblocks or
	none of the free memblocks is big enough to support the incoming request*/

	/*current_location_mb walked off the free list and is NULL, prev_location_mb 
	holds the last free memblock if it isn't NULL*/
	current_location=(void*) prev_location_mb; 
	/*If the free list of memblocks was existant...*/
	if(current_location!=NULL){
		/*then move to the beginning of the data segment*/
		current_location=current_location+sizeof(struct memblock);
	}

	/*If the last free memblock was the last memblock on the heap...*/
	if((current_location!=NULL)&&(current_location+prev_location_mb->memsize==last_valid_address)){ 
		/*then extend the heap as well as the last memblock so it can support the incoming request*/
		current_location=last_valid_address;
		temp=size_to_increase_heap(size);
		last_valid_address=(void*)sbrk(temp);
		temp=last_valid_address-current_location;
		prev_location_mb->memsize=prev_location_mb->memsize+temp;
		prev_location_mb->nextblock=NULL;
		current_location=(void*)prev_location_mb;
		current_location=current_location+sizeof(struct memblock);
		memory_location=current_location;
		return memory_location;
	/*If the last free memblock was not the last memblock on the heap...*/
	}else{ 
		/*Then extend the heap and create a new memblock to hold its size*/
		current_location=last_valid_address;
		memory_location=current_location;
		temp=size_to_increase_heap(size);
		last_valid_address=(void*)sbrk(temp); //4K
		current_location_mb=(struct memblock*)current_location;
		current_location_mb->memsize=(last_valid_address-current_location)-sizeof(struct memblock);
		current_location_mb->nextblock=NULL;
		/*If we are here because the free list of memblocks was non-existant then...*/
		if(begin_freelist==NULL){
			/*Make the newly created memblock the first free memblock*/
			begin_freelist=current_location_mb;
		}else{
			/*Otherwise link the last free memblock to the new free memblock so it is on the list*/
			prev_location_mb->nextblock=current_location_mb;
		}
		return memory_location;
	}
}
  

/****************************************************** 
  free1 - frees memory back to the user. Keeps integrity
    of the linked list structure which is very important
    to all of this working properly. Does nothing if the 
    argument is NULL.

  Arguments: ptr - the pointer to the memory that needs
    to be moved to the freed memory list so it can be reused
*******************************************************/
void free(void *ptr){
  void* prev;
  void* curr;
  if(ptr==NULL){
    return; 
  }
  struct memblock* current_location_mb=NULL;
  struct memblock* prev_location_mb=NULL;
  current_location_mb=begin_freelist;
  prev_location_mb=begin_freelist;
  /*Search the free list of memblocks*/
  while(current_location_mb!=NULL){
    /*If the memory trying to be freed is already free then return*/ 
    if(current_location_mb==(struct memblock*)ptr-sizeof(struct memblock)){ 
      return;
    }
    /*Join together adjacent free blocks of memory*/
    prev=(void*)prev_location_mb;
    curr=(void*)current_location_mb;
    prev=prev+sizeof(struct memblock);
    curr=curr-prev_location_mb->memsize;
    /*if two free memblocks are next to eachother in memory*/
    
    if(curr==prev){ 
      /*resize the previous memblock to engulf the later memblock*/
      prev_location_mb->memsize=prev_location_mb->memsize+sizeof(struct memblock)+current_location_mb->memsize;
      /*Keep the integrity of the free list*/
      prev_location_mb->nextblock=current_location_mb->nextblock;
    }
    current_location_mb=current_location_mb->nextblock;
    if(prev_location_mb->nextblock!=current_location_mb){
      prev_location_mb=prev_location_mb->nextblock;
    }
  }
  
  /*If the free list of memblocks was non-existant...*/
  if(begin_freelist==NULL){ 
    /*then put the memory on the freelist as the first element*/
    begin_freelist=(struct memblock*)ptr-sizeof(struct memblock);
  }else{
    /*Otherwise, add it to the end of the free list of memblocks*/
    prev_location_mb->nextblock=(struct memblock*)ptr-sizeof(struct memblock);
  }
  return;
}

/****************************************************** 
  calloc1 - creates memory wide enough to hold an array
     of a data type at 'nmemb' elements long and 'size' wide.
     Also clears the memory that is allocated. Returns NULL
     if either of the arguments is 0.

  Arguments: nmemb - the amount of elements in the array
     size - the size each array element will hold
*******************************************************/
void* calloc1(size_t nmemb, size_t size){
  void* returned_memory;
  if(nmemb==NOTHING || size==NOTHING){
    return (void*)NULL;
  }
  size=size_8(size);
  /*Make it big enough to support all elements of 
  the array for the required size*/
  size_t all_space=nmemb*size;
  /*allocate the memory*/
  returned_memory=malloc(all_space);
  /*clear the allocated memory*/
  returned_memory=memset(returned_memory,NOTHING,all_space);
  /*Finally return the cleared memory*/
  return returned_memory;
}

/****************************************************** 
  realloc1 - Moves data from ptr to a new spot in memory
    and allows that data to be resized. 
    Copies the old data and leaves newly allocated memory 
    uninitialized. The old data spot is then freed to the user.
    If ptr = NULL then this function will perform a malloc with 
    'size' as its argument. If the size is 0 then this function 
    will serve as a free of the memory pointed to by 'ptr'. 

  Arguments: ptr - The pointer to the data that will be moved.
     size - the size of the newly allocated space. Can be
        less than or greater than the old memory that is being
        moved. 
*******************************************************/
void* realloc1(void *ptr, size_t size){
  void* returned_memory=ptr;
  /*Go right before the memblock so we can get the memblock data*/
  returned_memory=returned_memory-sizeof(struct memblock);
  struct memblock* compare_me=(struct memblock*) returned_memory;
  size_t temp;
  /*If source memory is NULL then perform an allocation of the memory for the size*/
  if(ptr==NULL){
    return malloc(size);
  /*If the size is 0 then perform a free on the source memory*/
  }else if(size==NOTHING){
    free(ptr);
    return ptr;
  }
  /*Create new memory, copy over the minimum of the source memory 
  and the destination memory sizes*/
  if(size<compare_me->memsize){
    temp=size;
  }else{
    temp=compare_me->memsize;
  }
  returned_memory=malloc(temp);
  returned_memory=memcpy(returned_memory,ptr, temp);
  /*Free the old memory location*/
  free(ptr);
  return returned_memory;
}

/*int main(){
  int i=1;
  i++;
  exit(0);
}*/
