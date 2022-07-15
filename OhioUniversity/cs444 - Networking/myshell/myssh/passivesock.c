/* passivesock.c - passivesock */

#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#include "libnet.h"


static u_short portbase = 0;           /* port base, for non-root servers      */


/*------------------------------------------------------------------------
 * passivesock - allocate & bind a server socket using TCP or UDP
 *------------------------------------------------------------------------
 */
int
passivesock(
    char *service,		/* service associated with the desired port     */
    char *protocol,		/* name of protocol to use ("tcp" or "udp")     */
    int qlen)			/* maximum length of the server request queue   */
{
    struct servent  *pse;   /* pointer to service information entry */
    struct protoent *ppe;   /* pointer to protocol information entry*/
    struct sockaddr_in sin; /* an Internet endpoint address         */
    int     s, type;        /* socket descriptor and socket type    */

    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;

    /* Map service name to port number */
    if (service) {
	/* if service is NULL, don't bother */
	if (( pse = getservbyname(service, protocol) ))
	    sin.sin_port = htons(ntohs((u_short)pse->s_port)
				 + portbase);
	else if ( (sin.sin_port = htons((u_short)atoi(service))) == 0 )
	    Error("can't get \"%s\" service entry\n", service);
    }

    /* Map protocol name to protocol number */
    if ( (ppe = getprotobyname(protocol)) == 0)
	Error("can't get \"%s\" protocol entry\n", protocol);

    /* Use protocol to choose a socket type */
    if (strcmp(protocol, "udp") == 0)
	type = SOCK_DGRAM;
    else
	type = SOCK_STREAM;

    /* Allocate a socket */
    s = socket(PF_INET, type, ppe->p_proto);
    if (s < 0)
	Error("can't create socket: %s\n", strerror(errno));

    /* Bind the socket */
    if (service) {
	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	    Error("can't bind to %s port: %s\n", service,
		    strerror(errno));
    } /* Else, don't bind, let the OS pick random port */

    if (type == SOCK_STREAM && listen(s, qlen) < 0)
	Error("can't listen on %s port: %s\n", service,
		strerror(errno));
    return s;
}

