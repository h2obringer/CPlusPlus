/* tcpecho.c - main, tcpecho */

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
#define LINELEN         128


/* local routines */
static int reaper(void);
static int TCPechod(int fd);
static int tcpecho(char *host, char *service);
static void printHelp(void);
static int handleCommands(int fd);

/*globals*/
static int debug=0;
static int echoThis=0;	/*0 if no echo requested, 1 to implement echo*/

/* TCPechod.c - main, TCPechod */
/*------------------------------------------------------------------------
 * main - Concurrent TCP server for ECHO service
 *------------------------------------------------------------------------
 */
int main(int argc, char **argv){
        int i=0;
	int server_client=0; 		/*0 if unspecified (will exit program), 1 if server, 2 if host;*/
        char    *host = "localhost";    /* host to use if none supplied */
        char    *service = "5000";      /* default service name         */
        struct  sockaddr_in fsin;       /* the address of a client      */
        u_int   alen;                   /* length of client's address   */
        int     msock;                  /* master server socket         */
        int     ssock;                  /* slave server socket          */


  for(i=1;i<argc;++i){
    if(strcmp(argv[i],"-t")==0){
      if(i+1<argc){
        if(strcmp(argv[i+1],"s")==0){ /*set up a server*/
          server_client=1;
        }else if(strcmp(argv[i+1],"h")==0){ /*set up a host*/
          server_client=2;
        }
      }
    }
  }

  for (i=1; i < argc; ++i) {
    if(strcmp(argv[i],"-host")==0){		/*MAYBE A LITTLE WORK NEEDED*/
      if(server_client==1){ /*must be a server to specify this option*/
        if(i+1<argc){
          host=argv[i+1];
        }
      }
      ++i;
    }

    else if(strcmp(argv[i],"-port")==0){	/*MAYBE A LITTLE WORK NEEDED*/
      if(i+1<argc){
        if(server_client==1){
          if(strcmp(argv[i+1],"-")==0){
            service=NULL;
          }else{
            service=argv[i+1];
          }
        }else{
          service=argv[i+1];
        }
        ++i;
      }
    }

    /*DEBUG OPTION*/
    else if(strcmp(argv[i],"-d")==0){
      ++debug;
    }

    /*SET GROUP OPTION (already implemented)*/
    else if(strcmp(argv[i],"-t")==0){
      ++i; /*skip next argument so it doesn't become an unrecognized argument*/
    }
    
    else if(strcmp(argv[i],"-e")==0){
      ++echoThis;
    }

    /*HELP OPTION*/            
    else if(strcmp(argv[i],"-h")==0){ 
      printHelp(); /*mysshell print help function*/
      printf("Arguments given were:\n");
      for (i=1; i < argc; ++i) {
        printf("argv[%d]: '%s'\n", i, argv[i]);
      }
      exit(1);
    }

    else{
      printHelp(); /*mysshell print help function*/
      printf("Arguments given were:\n");
      for (i=1; i < argc; ++i) {
        printf("argv[%d]: '%s'\n", i, argv[i]);
      }
      exit(1);
    }
  }

  if(server_client==0){
    printHelp();
    exit(0);
  }else if(server_client==1){
        msock = passiveTCP(service, QLEN);

	printf("Server running on local port %u\n", lport(msock));

        signal(SIGCHLD, (void (*)())reaper);

        while (1) {
                alen = sizeof(fsin);
                fprintf(stdout,"About to accept socket\n");
                ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
                if (ssock < 0) {
                      
                fprintf(stderr, "usage: tcpecho [host [port]]\n");
                exit(1);  
                if (errno == EINTR)
                                continue;
                        Error("accept: %s\n", strerror(errno));
                }

                switch (fork()) {
                case 0:         /* child */
                        (void) close(msock);
                        if(echoThis>0){
                          exit(TCPechod(ssock));
                        }else{
                          exit(handleCommands(ssock));
                        }
                default:        /* parent */
                        (void) close(ssock);
                        break;
                case -1:
                        Error("fork: %s\n", strerror(errno));
                }
        }
  }else if(server_client==2){
    tcpecho(host, service);
  }

  exit(0);
}


/*------------------------------------------------------------------------
 * TCPechod - echo data until end of file
 *------------------------------------------------------------------------
 */
static int TCPechod(int fd){
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


static int handleCommands(int fd){
  int j;
  char buf[BUFSIZ];
  char tempBuf[BUFSIZ];
  int cc;
  FILE *f;
  char *cmd;
  char *pch;
  char line[256];

  cc = read(fd, buf, sizeof buf);
  /*if((cc = read(fd, buf, sizeof buf))!=0){ */
  /*while((cc = read(fd, buf, sizeof buf))!=0) {*/
	
    
  if (cc < 0)
  {
      Error("myssh read: %s\n", strerror(errno));
  } 
  else if( cc != 0 ) 
  {
    cmd = malloc(strlen(buf+10));
    for(j=0;j<strlen(buf)-2;++j){
      tempBuf[j]=buf[j];
    }
    tempBuf[strlen(tempBuf)-1]='\00';

    sprintf(cmd,"/bin/%s\n", tempBuf);

    f = popen(cmd, "r");

    while ((fgets(line,sizeof(line),f)) != NULL) {
	if ((pch = strchr(line,'\n')) != NULL) 
	    *pch = '\00';  /* nuke the newline*/
	puts(line);
        write(fd, line, strlen(line));
    }

    pclose(f);
    close(fd);
    fprintf(stdout,"closed the file descriptor\n");
  }
  
  
  return 0; 
}




static int tcpecho(char *host, char *service){
  char    buf[LINELEN+1];	/* buffer for one line of text  */
  int     s;		/* socket descriptor */
  int	len;
  int endCommand=0;

  s = connectTCP(host, service); /* connect as a Unix file descriptor (fd) */

  if(echoThis>0){ 
    while (1) {
      /*  read a line from stdin */
      if (fgets(buf, sizeof(buf), stdin) == NULL){
        break;
      }
      /* remove the newline */
      buf[strlen(buf)-1] = '\00';

      if(echoThis>0){
        fprintf(stderr,"You said: %s\n", buf);
      }

      /* send the characters down the TCP connection */
      strncat(buf,"\r\n",sizeof(buf));   /* tack on the official end of line sequence */
      if (write(s,buf,strlen(buf)) != strlen(buf)) {
        perror("write");
        exit(-2);
      }


      len = read(s,buf,sizeof(buf));
      if (len == 0) {
        /* EOF */
        break;
      }else if(len == -1){
	perror("read");
      }
      buf[len] = '\00';	/* NULL terminate so we can treat it as a string */

      fprintf(stderr,"The server sent %d chars: %s\n", len, buf);
    }
  }else{








/*FOR NORMAL PROGRAM*/

      /*  read a line from stdin */
      if (fgets(buf, sizeof(buf), stdin) == NULL){
        exit(0);
      }
      /* remove the newline */
      buf[strlen(buf)-1] = '\00';

      /* send the characters down the TCP connection */
      strncat(buf,"\r\n",sizeof(buf));   /* tack on the official end of line sequence */
      if (write(s,buf,strlen(buf)) != strlen(buf)) {
        perror("write");
        exit(-2);
      }
      /* read back an answer */
      while(endCommand==0){
        len=read(s,buf,sizeof(buf));
        if (len == 0) {
	  ++endCommand;/* EOF */
	  /*break; most recent*/
        }else if(len == -1){
          perror("read");
        }
        buf[len] = '\00';/* NULL terminate so we can treat it as a string */
        fprintf(stdout,"%s\n",buf);
      }
  }/*end else*/

/*END FOR NORMAL PROGRAM*/
  return(0);



}





















/*------------------------------------------------------------------------
 * reaper - clean up zombie children
 *------------------------------------------------------------------------
 */
static int reaper(void){
    int status;
    int pid;
    pid_t wait3(int *statusp, int options, struct rusage *rusage);

    while ((pid=wait3(&status, WNOHANG, NULL)) > 0) {
	if (debug>0)
	    printf("process %d reaped\n", pid);
	/* empty */;
    }

    /* re-install myself for the next child */
    signal(SIGCHLD, (void (*)())reaper);

    return(0);
}

static void printHelp(void){
  fprintf(stderr, "\n\nmysshell help: Program usage depends on whether a \n");
  fprintf(stderr, "\tserver or a host is desired to be set up\n\n");
  fprintf(stderr, "Usage if server is desired: ./mysshell -t s [-d] [-e] [-h] [-port P]\n");
  fprintf(stderr, "Usage if host is desired: ./mysshell -t h [-d] [-e] [-h] [-host H [port P]]\n\n");
  fprintf(stderr, "Please note that -host and -port options must be the last arguments given.\n\n");
  fprintf(stderr, "-t s: set up a server.\n");
  fprintf(stderr, "-t h: set up a host.\n");
  fprintf(stderr, "[-d]: debug mode.\n");
  fprintf(stderr, "[-e]: set up connection as an echo service instead of as a command prompt.\n");
  fprintf(stderr, "[-h]: print the help screen and exit.\n");
  fprintf(stderr, "[-host] H: set up a host on H.\n");
  fprintf(stderr, "[-port] P: set up a port on P (Use '-' to specify a random port.\n");
}








