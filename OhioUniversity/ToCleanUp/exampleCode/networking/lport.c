/* lport.c - return the local port number used by an open TCP/UDP socket */
/* Shawn Ostermann -- Fri Mar  1, 1996 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


unsigned short
lport(
    int fd)
{
    unsigned short port;
    struct sockaddr_in sin;
    unsigned int sinlen;

    sinlen = sizeof(sin);
    if (getsockname(fd, (struct sockaddr *)&sin, &sinlen) != 0) {
	perror("getsockname");
	exit(-1);
    }

    port = ntohs(sin.sin_port);

    return(port);
}

