/* 
 * The basic data-structures and interface function definitions
 * that are part of the vrouter (virtual router) library.
 * 
 * Manikantan Ramadas, 5 Dec 2004
 *
 * Version 2.1 - Thu May 15 11:47:37 2008
 * Version 2.2 - Mon May 19 15:03:02 2008
 *
 */

#ifndef vrouter_h
#define vrouter_h


#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdarg.h>


typedef struct _lan
{
	char lname[6]; // lan name : "eth1" - "eth16"
	char hwaddr[18]; // of the form : "aa:bb:cc:dd:ee:ff"
	struct _lan *next; // if we want to be in a linked-list
} lan;

typedef struct _lanlist
{
	int cnt; // number of elements in this list
	struct _lan *lan; // pointer to the first guy
} lanlist;

// This function, typically called by a vrouter application upon initiation
// returns the list of all available lans. 
// Returns NULL upon failure
lanlist* whichlans(void);

//
// tell vrouter what group number you're using.  This must be called before anything else!
// return value is 1 if it succeeds and 0 if it's an illegal group number
//
int setgroup(unsigned int group);

// The goal is to emulate a scheme analogous to the "FILE*" scheme
// used for FILE IO.
// This function returns an INTERFACE* structure. 
// It chooses a UDP port to bind to based on the iname and group given.
// 
// Returns NULL upon failure.
// Warning: the second argument, group, was removed between the vi and vos projects
//   for backward compatibility, it's now optional (or as optional as C allows).  Correct behavior
//   with vos projects still requires you to call setgroup(group) first (see above)    
typedef struct _INTERFACE INTERFACE;
INTERFACE* openinterface(char *lname, ...);

// This function reads (hopefully) a single packet from the INTERFACE
// The buffer given to us by the application better be big enough to hold
// an MTU size packet.
//
// Returns the number of bytes read upon success or -1 upon failure.

int readpacket(INTERFACE *iface, void *buf, int len);

// This function writes the given packet on the INTERFACE.
// 
// Returns the number of bytes written upon success or -1 upon failure.
int writepacket(INTERFACE *iface, void *buf, int len);

// Closing the INTERFACE
// 
// Returns 0 upon success or -1 upon failure.
int closeinterface(INTERFACE *iface);

// see if a packet is available for reading on 'iface'
// returns 1 if at least one packet is available
// returns 0 if NO packet is available
int checkforpacket(INTERFACE *iface);

// block until a packet is available on one of the interfaces
//   specified ifaces must be an array of interfaces handles, the last
//   of which must be NULL
// returns the number of interfaces with packets available
int blockforpacket(INTERFACE *ifaces[]);
// this form is the same, but will ONLY block for 'msec_maxwait' milliseconds
// returns the number of interfaces with packets available (or 0 for timeout)
int blockforpacket_timeout(INTERFACE *ifaces[],int msec_maxwait);

// read the IPv6 prefix/length assigned to a specified interface
//   prefix_addr is the buffer (space already allocated by you) to store the prefix
//   prefix_length is the address of an unsigned integer to store the prefix length into
// returns 1 if it succeeds and 0 otherwise
// this routine only works on VOS nodes with multiple interfaces    
int readipprefixfor(INTERFACE *iface, void *prefix_addr, unsigned int *prefix_length);

// A simple IP checksum function
// Calculates and returns a 16-bit IP style checksum on len bytes
// beginning at ptr
// Return 16-bit ones complement of 16-bit sum.
u_short vchksum(void* ptr, int len);
        
#ifdef __cplusplus
}
#endif

#endif /* vrouter_h */
