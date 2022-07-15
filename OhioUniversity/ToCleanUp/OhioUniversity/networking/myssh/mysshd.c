/****************************************
* Author: Randal Mark Obringer
* CoAuthor: Dr. Ostermann
*
* Description: This is the client program of the 
*   myssh project. It must be run after and only
*   after starting the server program.
*
*
*****************************************/
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
#define BUFSIZE         4096    /*size of the buffer to use*/
#define LINELEN         256     /*length of a line*/

/* local routines */
static int reaper(void);
static int handleCommands(int fd,char* pword);

/* globals */
static int debug = 0;
/*------------------------------------------------------------------------
 * main - server program
 *------------------------------------------------------------------------
 */
int main(int argc,char **argv){
	int i=0;
	int j=0;
	char    *service = "5000";      /* service name or port number  */
	struct  sockaddr_in fsin;       /* the address of a client      */
	u_int   alen;                   /* length of client's address   */
	int     msock;                  /* master server socket         */
	int     ssock;                  /* slave server socket          */
	char password[LINELEN+1];

	for(i=0;i<argc;++i){
		/*SPECIFY THE PORT OPTION*/
		/*fprintf(stdout,"argc= %d\n",argc);*/
		if(strcmp(argv[i],"-port")==0){	
			if(i+1<argc){
				if(strcmp(argv[i+1],"-")==0){
					service=NULL;
				}else{
					service=argv[i+1];
				}
			}
			++i;
		}

		/*DEBUG OPTION*/
		else if(strcmp(argv[i],"-d")==0){
			++debug;
		}

		/*HELP OPTION*/            
		else if(strcmp(argv[i],"-h")==0){ 
			mysshdHelp(); /*myssh print help function*/
			printf("Arguments given were:\n");
			for (j=1; j < argc; ++j) {
				printf("argv[%d]: '%s'\n", i, argv[i]);
			}
			exit(1);
		}
	}/*END PARSING COMMAND LINE ARGUMENTS*/

	fprintf(stdout,"Enter a password for all incoming connections:\n");
	if (fgets((char*) password, 2048, stdin) == NULL){ /*set a password for all connections*/
		exit(0);
	}
        
	/* remove the newline */
	password[strlen(password)-1] = '\00';

	if(debug>0){/*print back out the password you set*/
		fprintf(stdout,"Your password is: %s\n",password);
	}

	msock = passiveTCP(service, QLEN);
	printf("Server running on local port %u\n", lport(msock));/*verify what port we are running on*/

	signal(SIGCHLD, (void (*)())reaper); /*Dr. Ostermann's process cleaning function*/

	while (1) {
		alen = sizeof(fsin);
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
		if (ssock < 0) {
			if (errno == EINTR){
				continue;
			}
			Error("accept: %s\n", strerror(errno));
		}
		switch (fork()) {
			case 0:         /* child */
				(void) close(msock);
				exit(handleCommands(ssock,(char*)password)); /*handle commands given from the client then kill the process and await another connection*/
			default:        /* parent */
				(void) close(ssock);
				break;
			case -1:
				Error("fork: %s\n", strerror(errno));
		}
	}
}


/*------------------------------------------------------------------------
 * handleCommands - verify password then accept commands to execute
 *------------------------------------------------------------------------
 */
static int handleCommands(int fd,char* pword){
	int j; 
	char buf[BUFSIZ];/*buffer to read and write to*/
	int cc;/*size of read or written data*/
	FILE *f; /*hold file descriptor from the process we will create*/
	char *cmd; /*holds the command we want to execute*/
	char line[256]; /*holds strings created from the command that was executed*/
	char compare[BUFSIZ]; /*string to hold the password received from the client, we will compare it to the server's password*/
	char confirmation[BUFSIZ]; /*string to hold the confirmation to send to the client that tells whether a password was good or not*/
	compare[0]='N'; /*initial these strings*/
	compare[1]='O';
	compare[2]='\00';
	compare[3]='\r';
	compare[4]='\n';
	confirmation[0]='N';
	confirmation[1]='O';
	confirmation[2]='\00';
	confirmation[3]='\r';
	confirmation[4]='\n';

	while(1){/*sit here until we receive a good password from a client*/
		cc=read(fd,compare,sizeof(compare)); /*read in the password*/
		decrypt_data(compare); /*decrypt the password sent from the client*/
		for(j=0;compare[j]!=NULL;++j){ /*NULL terminate the password*/
			if((compare[j]=='\r')||(compare[j]=='\n')){
				compare[j]='\00';
			}
		}
		if(strcmp(pword,compare)==0){/*if the passwords match then send a good confirmation so client will begin sending commands*/
			if(debug>0){
				fprintf(stdout,"The password from the client was good. We will now execute its command\n");
			}
			confirmation[0]='Y';
			confirmation[1]='E';
			confirmation[2]='S';
			confirmation[3]='\r';
			confirmation[4]='\n';
			confirmation[5]='\00';
			encrypt_data(confirmation);
			write(fd, (char*)confirmation, strlen(confirmation));
			break;
		}else{/*otherwise send a bad confirmation*/
			encrypt_data(confirmation);
			write(fd, (char*)confirmation, strlen(confirmation));
		}
	}

	/*retreive the command*/
	cc = read(fd, buf, sizeof buf);
	decrypt_data(buf);	
    
	if (cc < 0){
		Error("myssh read: %s\n", strerror(errno));
	}else if( cc != 0 ) /*if a command was read in*/{
		cmd = malloc(strlen(buf+10));
		for(j=0;buf[j]!=NULL;++j){
			if((buf[j]=='\r')||(buf[j]=='\n')){/*get rid of the return carrage and newline characters*/
				buf[j]='\00';
			}
		}

		sprintf(cmd,"/bin/%s\n", buf); /*build up the command */

		f = popen(cmd, "r"); /*start a process for the command*/

		while ((fgets(line,sizeof(line),f)) != NULL) {/*read the characters produced from the command process*/
			for(j=0;line[j]!=NULL;++j){
				if((line[j]=='\r')||(line[j]=='\n')){/*get rid of the return carrage and newline characters*/
					line[j]='\00';
				}
			}

			if(debug>0){
				puts(line); /*display on the server side before adding official end of line characters*/
			}

			strncat(line,"\r\n\00",sizeof(line));/*add end of line characters*/ 
			encrypt_data(line);
			write(fd, line, strlen(line));/*send them to the host*/
		}

		pclose(f);
		close(fd);
		if(debug>0){
			fprintf(stdout,"closed the file descriptor\n");
		}
	}
	return 0;
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
		if (debug)
			printf("process %d reaped\n", pid);
		/* empty */;
	}

	/* re-install myself for the next child */
	signal(SIGCHLD, (void (*)())reaper);

	return(0);
}
