/* tcpecho.c - main, tcpecho */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "libnet.h"


#define LINELEN         128

static int tcpecho(char *host, char *service);


/*------------------------------------------------------------------------
 * main - TCP client for ECHO service
 *------------------------------------------------------------------------
 */
int
main(int argc, char **argv)
{
        char    *host = "localhost";    /* host to use if none supplied */
        char    *service = "echo";      /* default service name         */

        switch (argc) {
        case 1:
                host = "localhost";
                break;
        case 3:
                service = argv[2];
                /* FALL THROUGH */
        case 2:
                host = argv[1];
                break;
        default:
                fprintf(stderr, "usage: tcpecho [host [port]]\n");
                exit(1);
        }

        tcpecho(host, service);

        exit(0);
}

/*------------------------------------------------------------------------
 * tcpecho - send input to ECHO service on specified host and print reply
 *------------------------------------------------------------------------
 */
int
tcpecho(char *host, char *service)
{
        char    buf[LINELEN+1];	/* buffer for one line of text  */
        int     s;		/* socket descriptor */
	int	len;

        s = connectTCP(host, service); /* connect as a Unix file descriptor (fd) */

	while (1) {
	    /*  read a line from stdin */
	    if (fgets(buf, sizeof(buf), stdin) == NULL)
		break;

	    /* remove the newline */
	    buf[strlen(buf)-1] = '\00';
	    fprintf(stderr,"You said: %s\n", buf);

	    /* send the characters down the TCP connection */
	    strncat(buf,"\r\n",sizeof(buf));   /* tack on the official end of line sequence */
	    if (write(s,buf,strlen(buf)) != strlen(buf)) {
		perror("write");
		exit(-2);
	    }

	    /* read back an answer */
	    len = read(s,buf,sizeof(buf));
	    if (len == 0) {
		/* EOF */
		break;
	    }  else if (len == -1) {
		perror("read");
	    }
	    buf[len] = '\00';	/* NULL terminate so we can treat it as a string */
	    fprintf(stderr,"The server sent %d chars: %s\n", len, buf);
        }

	return(0);
}
