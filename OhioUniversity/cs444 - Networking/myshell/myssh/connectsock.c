/* connectsock.c - connectsock */

#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "libnet.h"




/*------------------------------------------------------------------------
 * connectsock - allocate & connect a socket using TCP or UDP
 *------------------------------------------------------------------------
 */
int
connectsock(
    char *host,			/* name of host to which connection is desired  */
    char *service,		/* service associated with the desired port     */
    char *protocol)		/* name of protocol to use ("tcp" or "udp")     */
{
    struct hostent  *phe;	/* pointer to host information entry    */
    struct servent  *pse;	/* pointer to service information entry */
    struct protoent *ppe;	/* pointer to protocol information entry*/
    struct sockaddr_in sin;	/* an Internet endpoint address         */
    int s, type;		/* socket descriptor and socket type    */


    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;

    /* Map service name to port number */
    if ((pse = getservbyname(service, protocol)))
	sin.sin_port = pse->s_port;
    else if ((sin.sin_port = htons((u_short)atoi(service))) == 0 )
	Error("can't get '%s' service entry", service);

    /* Map host name to IP address, allowing for dotted decimal */
    if ((phe = gethostbyname(host)))
	bcopy(phe->h_addr, (char *)&sin.sin_addr, phe->h_length);
    else if ((sin.sin_addr.s_addr = inet_addr(host)) == -1 )
	Error("can't get '%s' host entry", host);

    /* Map protocol name to protocol number */
    if ((ppe = getprotobyname(protocol)) == 0)
	Error("can't get '%s' protocol entry", protocol);

    /* Use protocol to choose a socket type */
    if (strcmp(protocol, "udp") == 0)
	type = SOCK_DGRAM;
    else
	type = SOCK_STREAM;

    /* Allocate a socket */
    s = socket(PF_INET, type, ppe->p_proto);
    if (s < 0)
	SysError("can't create socket");

    /* Connect the socket */
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	SysError("can't connect to %s.%s", host, service);

    return s;
}
