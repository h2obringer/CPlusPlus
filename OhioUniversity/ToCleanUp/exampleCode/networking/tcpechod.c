/* TCPechod.c - main, TCPechod */

#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <string.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "libnet.h"

#define QLEN               5    /* maximum connection queue length      */
#define BUFSIZE         4096

/* local routines */
static int reaper(void);
static int TCPechod(int fd);

/* globals */
static int debug = 1;


/*------------------------------------------------------------------------
 * main - Concurrent TCP server for ECHO service
 *------------------------------------------------------------------------
 */
int
main(argc, argv)
int     argc;
char    *argv[];
{
        char    *service = "echo";      /* service name or port number  */
        struct  sockaddr_in fsin;       /* the address of a client      */
        u_int   alen;                   /* length of client's address   */
        int     msock;                  /* master server socket         */
        int     ssock;                  /* slave server socket          */

        switch (argc) {
        case    1:
                break;
        case    2:
                service = argv[1];
                break;
        default:
                Error("usage: TCPechod [port]\n");
        }

	/* if the port is "-", use a random port */
	if (strcmp(service,"-") == 0)
	    service = NULL;

        msock = passiveTCP(service, QLEN);

	printf("Server running on local port %u\n", lport(msock));

        signal(SIGCHLD, (void (*)())reaper);

        while (1) {
                alen = sizeof(fsin);
                ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
                if (ssock < 0) {
                        if (errno == EINTR)
                                continue;
                        Error("accept: %s\n", strerror(errno));
                }
                switch (fork()) {
                case 0:         /* child */
                        (void) close(msock);
                        exit(TCPechod(ssock));
                default:        /* parent */
                        (void) close(ssock);
                        break;
                case -1:
                        Error("fork: %s\n", strerror(errno));
                }
        }
}


/*------------------------------------------------------------------------
 * TCPechod - echo data until end of file
 *------------------------------------------------------------------------
 */
static int
TCPechod(
    int     fd)
{
        char    buf[BUFSIZ];
        int     cc;

        while ((cc = read(fd, buf, sizeof buf))!=0) {
                if (cc < 0)
                        Error("echo read: %s\n", strerror(errno));
                if (write(fd, buf, cc) < 0)
                        Error("echo write: %s\n", strerror(errno));
        }
        return 0;
}

/*------------------------------------------------------------------------
 * reaper - clean up zombie children
 *------------------------------------------------------------------------
 */
static int
reaper(void)
{
    int status;
    int pid;
    pid_t wait3(int *statusp, int options, struct rusage *rusage);

    while ((pid=wait3(&status, WNOHANG, NULL)) > 0) {
	if (debug)
	    printf("process %d reaped\n", pid);
	/* empty */;
    }

    /* re-install myself for the next child */
    signal(SIGCHLD, (void (*)())reaper);

    return(0);
}
