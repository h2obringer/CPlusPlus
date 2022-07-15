int
tcpecho(char *host, char *service)
{
        char    buf[LINELEN+1];	/* buffer for one line of text  */
        int     s;		/* socket descriptor */
	int	len;

        s = connectTCP(host, service); /* connect as a Unix file descriptor (fd) */

	fprintf(stdout,"tcp service succeeded\n");

	while (1) {
	    /*  read a line from stdin */
	    if (fgets(buf, sizeof(buf), stdin) == NULL)
		break;

	fprintf(stdout,"in the while loop of tcpecho after fgets\n");

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

/*------------------------------------------------------------------------
 * main - TCP client for ECHO service
 *------------------------------------------------------------------------
 */
int
main(int argc, char **argv) //client code
{
	int echoThis=0;			//0 if no echo requested, 1 to implement echo
	int server_client=0; 		//0 if unspecified (will exit program), 1 if server, 2 if host;
        char    *host = "localhost";    /* host to use if none supplied */
        char    *service = NULL;      /* default service name         */
        struct  sockaddr_in fsin;       /* the address of a client      */
        u_int   alen;                   /* length of client's address   */
        int     msock;                  /* master server socket         */
        int     ssock;                  /* slave server socket          */


  for(i=1;i<argc;++i){
    if(strcmp(argv[i],"-t")==0){
      if(i+1<argc){
        if(strcmp(argv[i+1],"s")==0){ //set up a server
          server_client=1;
        }else if(strcmp(argv[i+1],"h"==0){ //set up a host
          server_client=2;
        }
      }
    }
  }

  for (i=1; i < argc; ++i) {
    if(server_client==1){ //must be a server to specify this option
      if(strcmp(argv[i],"-host")==0){		//MAYBE A LITTLE WORK NEEDED
        if(i+1<argc){
          host=argv[i+1];
        }
      }
    }

    else if(strcmp(argv[i],"-port")==0){	//MAYBE A LITTLE WORK NEEDED
      if(i+1<argc){
        service=argv[i+1];
      }
    }

    /*DEBUG OPTION*/
    else if(strcmp(argv[i],"-d")==0){
      ++debug;
    }

    /*SET GROUP OPTION (already implemented)*/
    else if(strcmp(argv[i],"-t")==0){
      ++i; //skip next argument so it doesn't become an unrecognized argument
    }
    
    else if(strcmp(argv[i],"-e")==0){
      ++echoThis;
    }

    /*HELP OPTION*/            
    else if(strcmp(argv[j],"-h")==0){ 
      printHelp(); //mysshell print help function
      printf("Arguments given were:\n");
      for (j=1; j < argc; ++j) {
        printf("argv[%d]: '%s'\n", j, argv[j]);
      }
      exit(1);
    }

    else{
      printHelp(); //mysshell print help function
      printf("Arguments given were:\n");
      for (j=1; j < argc; ++j) {
        printf("argv[%d]: '%s'\n", j, argv[j]);
      }
      exit(1);
    }
  }

  if(echoThis>0){
    if(server_client==1){

        msock = passiveTCP(service, QLEN);

	printf("Server running on local port %u\n", lport(msock));

        signal(SIGCHLD, (void (*)())reaper);

        while (1) {
                alen = sizeof(fsin);
                ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
                if (ssock < 0) {
                      
                fprintf(stderr, "usage: tcpecho [host [port]]\n");
                exit(1);  if (errno == EINTR)
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
    }else if(server_client==2){
      tcpecho(host, service);
    }
  }
  exit(0);
}

/*------------------------------------------------------------------------
 * tcpecho - send input to ECHO service on specified host and print reply
 *------------------------------------------------------------------------
 */

void printHelp(){
  fprintf(stderr, "mysshell help: Program usage depends on whether a \n");
  fprintf(stderr, "\tserver or a host is desired to be set up\n");
  fprintf(stderr, "Usage if server is desired: ./mysshell -t s [-d] [-e] [-h] [-port P]");
  fprintf(stderr, "Usage if host is desired: ./mysshell -t h [-d] [-e] [-h] [-host H [port P]]\n\n");
  fprintf(stderr, "Please note that -host and -port options must be the last arguments given.\n");
  fprintf(stderr, "-t s: set up a server.\n");
  fprintf(stderr, "-t h: set up a host.\n");
  fprintf(stderr, "[-d]: debug mode.\n");
  fprintf(stderr, "[-e]: set up connection as an echo service instead of as a command prompt.\n");
  fprintf(stderr, "[-h]: print the help screen and exit.\n");
  fprintf(stderr, "[-host] H: set up a host on H.\n");
  fprintf(stderr, "[-port] P: set up a port on P (Use '-' to specify a random port.\n");
}
